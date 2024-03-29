{-# LANGUAGE FlexibleInstances, OverloadedStrings, BangPatterns #-}

module Language.Nano.TypeCheck where

import Language.Nano.Types
import Language.Nano.Parser

import qualified Data.List as L
import           Text.Printf (printf)  
import           Control.Exception (throw)
import System.Environment.Blank (getArgs)

--------------------------------------------------------------------------------
typeOfFile :: FilePath -> IO Type
typeOfFile f = parseFile f >>= typeOfExpr

typeOfString :: String -> IO Type
typeOfString s = typeOfExpr (parseString s)

typeOfExpr :: Expr -> IO Type
typeOfExpr e = do
  let (!st, t) = infer initInferState preludeTypes e
  if (length (stSub st)) < 0 then throw (Error ("count Negative: " ++ show (stCnt st)))
  else return t

--------------------------------------------------------------------------------
-- Problem 1: Warm-up
--------------------------------------------------------------------------------

-- | Things that have free type variables
class HasTVars a where
  freeTVars :: a -> [TVar]

-- | Type variables of a type
instance HasTVars Type where
  freeTVars (TInt) = []
  freeTVars (TBool) = []
  freeTVars (TVar a) = [a]
  freeTVars (x:=>y) = L.nub(freeTVars x ++ freeTVars y)
  freeTVars (TList a) = freeTVars a

-- | Free type variables of a poly-type (remove forall-bound vars)
instance HasTVars Poly where
  freeTVars (Mono a) = freeTVars a
  freeTVars (Forall a b) = L.delete a (L.nub(freeTVars b))



-- | Free type variables of a type environment
instance HasTVars TypeEnv where
  freeTVars gamma   = concat [freeTVars s | (x, s) <- gamma]  
  
-- | Lookup a variable in the type environment  
lookupVarType :: Id -> TypeEnv -> Poly
lookupVarType x ((y, s) : gamma)
  | x == y    = s
  | otherwise = lookupVarType x gamma
lookupVarType x [] = throw (Error ("unbound variable: " ++ x))

-- | Extend the type environment with a new biding
extendTypeEnv :: Id -> Poly -> TypeEnv -> TypeEnv
extendTypeEnv x s gamma = (x,s) : gamma  

-- | Lookup a type variable in a substitution;
--   if not present, return the variable unchanged
lookupTVar :: TVar -> Subst -> Type
lookupTVar a ((y,s) : xs)
      | a == y = s
      | otherwise = lookupTVar a xs
lookupTVar a [] = TVar a



-- | Remove a type variable from a substitution
removeTVar :: TVar -> Subst -> Subst
removeTVar a ((y,s):xs) 
      | a == y = removeTVar a xs
      | otherwise = (y,s) : removeTVar a xs
removeTVar a [] = []
     
-- | Things to which type substitutions can be apply
class Substitutable a where
  apply :: Subst -> a -> a
  
-- | Apply substitution to type
instance Substitutable Type where  
  apply _ TInt = TInt 
  apply _ TBool = TBool 
  apply sub (x:=>y) = (apply sub x) :=> (apply sub y)
  apply sub (TVar t) = lookupTVar t sub
  apply sub (TList t) = TList (apply sub t)

-- | Apply substitution to poly-type
instance Substitutable Poly where    
  apply sub (Mono s) = Mono(apply sub s) -- monotype apply 
  apply sub (Forall s p) = apply (removeTVar s sub) p


-- | Apply substitution to (all poly-types in) another substitution
instance Substitutable Subst where  
  apply sub to = zip keys $ map (apply sub) vals
    where
      (keys, vals) = unzip to
      
-- | Apply substitution to a type environment
instance Substitutable TypeEnv where  
  apply sub gamma = zip keys $ map (apply sub) vals
    where
      (keys, vals) = unzip gamma
      
-- | Extend substitution with a new type assignment
extendSubst :: Subst -> TVar -> Type -> Subst
extendSubst sub a t = apply sub [(a,t)] ++ apply [(a,t)] sub
      
--------------------------------------------------------------------------------
-- Problem 2: Unification
--------------------------------------------------------------------------------
      
-- | State of the type inference algorithm      
data InferState = InferState { 
    stSub :: Subst -- ^ current substitution
  , stCnt :: Int   -- ^ number of fresh type variables generated so far
} deriving (Eq,Show)

-- | Initial state: empty substitution; 0 type variables
initInferState = InferState [] 0

-- | Fresh type variable number n
freshTV n = TVar $ "a" ++ show n      
    
-- | Extend the current substitution of a state with a new type assignment   
extendState :: InferState -> TVar -> Type -> InferState
extendState (InferState sub n) a t = InferState (extendSubst sub a t) n
        
-- | Unify a type variable with a type; 
--   if successful return an updated state, otherwise throw an error
unifyTVar :: InferState -> TVar -> Type -> InferState
unifyTVar st a t 
   | (TVar a) == t = st
   | L.elem a (freeTVars t) = throw(Error ("type error: cannot unify " ++ (show a) ++ " and " ++ (show t)))
   | otherwise = extendState st a t
    
-- | Unify two types;
--   if successful return an updated state, otherwise throw an error
unify :: InferState -> Type -> Type -> InferState
unify st t1 t2 = case (t1,t2) of
  (TInt,TInt) -> st
  (TBool, TBool) -> st
  (TVar t, x) -> unifyTVar st t x
  (x, TVar t) -> unifyTVar st t x
  (TList t, TList t2) -> unify st t t2 --Goes thru the list to find type variables
  (a:=>b, c:=>d) -> unify (unify st a c) b d-- B and D should have an apply function
  -- 
  (x,y) -> throw(Error ("type error: cannot unify " ++ (show x) ++ " and " ++ (show y)))

--------------------------------------------------------------------------------
-- Problem 3: Type Inference
--------------------------------------------------------------------------------    
  
infer :: InferState -> TypeEnv -> Expr -> (InferState, Type)
infer st _   (EInt _)          = (st,TInt)
infer st _   (EBool _)         = (st,TBool) 
infer st gamma (EVar x)        = error "TBD: infer ELam" -- x
infer st gamma (ELam x body)   = error "TBD: infer ELam" -- \x -> y
infer st gamma (EApp e1 e2)    = error "TBD: infer EApp" -- -> x y
infer st gamma (ELet x e1 e2)  = error "TBD: infer ELet" -- let x = 5
infer st gamma (EBin op e1 e2) = infer st gamma asApp
  where
    asApp = EApp (EApp opVar e1) e2
    opVar = EVar (show op)
infer st gamma (EIf c e1 e2) = infer st gamma asApp
  where
    asApp = EApp (EApp (EApp ifVar c) e1) e2
    ifVar = EVar "if"    
infer st gamma ENil = infer st gamma (EVar "[]")

-- | Generalize type variables inside a type
generalize :: TypeEnv -> Type -> Poly
generalize gamma t = L.foldl f base args
                        where
                          f b c = Forall c b
                          base  = Mono t
                          args  = L.nub ((freeTVars t) L.\\ (freeTVars gamma))
    
-- | Instantiate a polymorphic type into a mono-type with fresh type variables
instantiate :: Int -> Poly -> (Int, Type)
instantiate n (Mono s) =  (n,s)
instantiate n (Forall tvar pol) = instantiate(n+1) (apply [(tvar, freshTV n)] pol )
      
-- | Types of built-in operators and functions  
preludeTypes :: TypeEnv
preludeTypes =
  [ ("+",    Mono $ TInt :=> TInt :=> TInt)
  , ("-",    Mono $ TInt :=> TInt :=> TInt)
  , ("*",    Mono $ TInt :=> TInt :=> TInt)
  , ("/",    Mono $ TInt :=> TInt :=> TInt)
  , ("==",   Forall "a"(Mono $ "a" :=> "a" :=> TBool))
  , ("!=",   Forall "a"(Mono $ "a":=> "a" :=> TBool))
  , ("<",    Mono $ TInt :=> TInt :=> TBool)
  , ("<=",   Mono $ TInt :=> TInt :=> TBool)
  , ("&&",   Mono $ TBool :=> TBool :=> TBool)
  , ("||",   Mono $ TBool :=> TBool :=> TBool)
  , ("if",   Forall "a"(Mono $ TBool :=> "a" :=> "a" :=> "a"))
  -- lists: 
  , ("[]",   Forall "a"(Mono $ (TList "a")))
  , (":",    Forall "a"(Mono $ "a" :=> (TList "a") :=> (TList "a") ))
  , ("head", Forall "a"(Mono $ (TList "a") :=> "a"))
  , ("tail", Forall "a"(Mono $ (TList "a") :=> "a"))
  ]