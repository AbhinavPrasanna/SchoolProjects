{- | CSE 116: All about fold.

     For this assignment, you may use the following library functions:

     length
     append (++)
     map
     foldl'
     foldr
     unzip
     zip
     reverse

  Use www.haskell.org/hoogle to learn more about the above.

  Do not change the skeleton code! The point of this assignment
  is to figure out how the functions can be written this way
  (using fold). You may only replace the `error "TBD:..."` terms.

-}

module Hw3 where

import Prelude hiding (replicate, sum)
import Data.List (foldl')

foldLeft :: (a -> b -> a) -> a -> [b] -> a
foldLeft = foldl'

--------------------------------------------------------------------------------
-- | sqSum [x1, ... , xn] should return (x1^2 + ... + xn^2)
--
-- >>> sqSum []
-- 0
--
-- >>> sqSum [1,2,3,4]
-- 30
--
-- >>> sqSum [(-1), (-2), (-3), (-4)]
-- 30

sqSum :: [Int] -> Int
sqSum xs = foldLeft f base xs
  where
   f a x = (x*x) + a -- base element x is multiplied by itself and added by each subsequent element
   base  = 0 --base case is equal to 0 or if we reach the end results in 0s

--------------------------------------------------------------------------------
-- | `pipe [f1,...,fn] x` should return `f1(f2(...(fn x)))`
--
-- >>> pipe [] 3
-- 3
--
-- >>> pipe [(\x -> x+x), (\x -> x + 3)] 3
-- 12
--
-- >>> pipe [(\x -> x * 4), (\x -> x + x)] 3
-- 24

pipe :: [(a -> a)] -> (a -> a)
pipe fs   = foldLeft f base fs
  where
    f a x = (a.x) --the value a applied to the function x as the functions are nested
    base  = \x -> x --identity function is the base case where function x goes into x

--------------------------------------------------------------------------------
-- | `sepConcat sep [s1,...,sn]` returns `s1 ++ sep ++ s2 ++ ... ++ sep ++ sn`
--
-- >>> sepConcat "---" []
-- ""
--
-- >>> sepConcat ", " ["foo", "bar", "baz"]
-- "foo, bar, baz"
--
-- >>> sepConcat "#" ["a","b","c","d","e"]
-- "a#b#c#d#e"

sepConcat :: String -> [String] -> String
sepConcat sep []     = ""
sepConcat sep (x:xs) = foldLeft f base l
  where
    f a x            = a ++ sep ++ x --passing each subsequent value and using the separator string to generate the final value
    base             = x --base value or the head of the list
    l                = xs --tail of the list or each subsequent elements

intString :: Int -> String
intString = show

--------------------------------------------------------------------------------
-- | `stringOfList pp [x1,...,xn]` uses the element-wise printer `pp` to
--   convert the element-list into a string:
--
-- >>> stringOfList intString [1, 2, 3, 4, 5, 6]
-- "[1, 2, 3, 4, 5, 6]"
--
-- >>> stringOfList (\x -> x) ["foo"]
-- "[foo]"
--
-- >>> stringOfList (stringOfList show) [[1, 2, 3], [4, 5], [6], []]
-- "[[1, 2, 3], [4, 5], [6], []]"

stringOfList :: (a -> String) -> [a] -> String
stringOfList f xs = "[" ++ sepConcat ", " (map f xs) ++ "]"

--------------------------------------------------------------------------------
-- | `clone x n` returns a `[x,x,...,x]` containing `n` copies of `x`
--
-- >>> clone 3 5
-- [3,3,3,3,3]
--
-- >>> clone "foo" 2
-- ["foo", "foo"]

clone :: a -> Int -> [a]
clone x n = if(n==0)
            then []
            else [x] ++ clone x (n-1)

type BigInt = [Int]

--------------------------------------------------------------------------------
-- | `padZero l1 l2` returns a pair (l1', l2') which are just the input lists,
--   padded with extra `0` on the left such that the lengths of `l1'` and `l2'`
--   are equal.
--
-- >>> padZero [9,9] [1,0,0,2]
-- ([0,0,9,9],[1,0,0,2])
--
-- >>> padZero [1,0,0,2] [9,9]
-- ([1,0,0,2], [0,0,9,9])

padZero :: BigInt -> BigInt -> (BigInt, BigInt)
padZero l1 l2 = if (length l1 > length l2) 
                then (l1, clone 0 (length l1 - length l2) ++ l2)
                else if(length l1 < length l2)
                then (clone 0 (length l2 - length l1) ++ l1, l2)
                else (l1,l2)

--------------------------------------------------------------------------------
-- | `removeZero ds` strips out all leading `0` from the left-side of `ds`.
--
-- >>> removeZero [0,0,0,1,0,0,2]
-- [1,0,0,2]
--
-- >>> removeZero [9,9]
-- [9,9]
--
-- >>> removeZero [0,0,0,0]
-- []

removeZero :: BigInt -> BigInt
removeZero [] = []
removeZero (d:ds) = if(d==0) --if d==0
                    then removeZero ds --Remove Zero from the next set of subsequent elements
                    else (d:ds) --Print the first element and every subsequent element


--------------------------------------------------------------------------------
-- | `bigAdd n1 n2` returns the `BigInt` representing the sum of `n1` and `n2`.
--
-- >>> bigAdd [9, 9] [1, 0, 0, 2]
-- [1, 1, 0, 1]
--
-- >>> bigAdd [9, 9, 9, 9] [9, 9, 9]
-- [1, 0, 9, 9, 8]

bigAdd :: BigInt -> BigInt -> BigInt
bigAdd l1 l2     = removeZero res
  where
    (l1', l2')   = padZero l1 l2
    res          = foldLeft f base args
    f a x =     if (fst x + snd x) < 10
                then a ++ [fst x + snd x]
                else bigAdd a [(fst x + snd x) `div` 10]
                   ++ [(fst x + snd x) `mod` 10] -- Recursively call BigAdd to each next set of subsequent elements if the base
                   -- is greater than or equal to 10 and use modulus to get the rest of the remaining digits.
    base         = []
    args         = (zip l1' l2') --Merge the two elements in the same list


--------------------------------------------------------------------------------
-- | `mulByInt i n` returns the result of multiplying
--   the int `i` with `BigInt` `n`.
--
-- >>> mulByInt 9 [9,9,9,9]
-- [8,9,9,9,1]

mulByInt :: Int -> BigInt -> BigInt
mulByInt i n = if(i==0)
                then [0]
               else if(i==1)
                then n 
               else (pipe(clone (bigAdd n)(i - 1)) n)
                

--------------------------------------------------------------------------------
-- | `bigMul n1 n2` returns the `BigInt` representing the product of `n1` and `n2`.
--
-- >>> bigMul [9,9,9,9] [9,9,9,9]
-- [9,9,9,8,0,0,0,1]
--
-- >>> bigMul [9,9,9,9,9] [9,9,9,9,9]
-- [9,9,9,9,8,0,0,0,0,1]

bigMul :: BigInt -> BigInt -> BigInt
bigMul l1 l2 = res
  where
    (_, res) = foldLeft f base args
    f a x    = (fst a ++ [0],bigAdd (snd a)  ((mulByInt x l1) ++ (fst a)))
    base     =  ([],[0])
    args     = reverse l2
