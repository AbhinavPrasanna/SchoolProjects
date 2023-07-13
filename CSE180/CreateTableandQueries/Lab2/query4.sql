SELECT DISTINCT m.name as theMonster, c.name as theCharacter, c.role as theRole
FROM  Characters c, Battles b,Monsters m
WHERE
c.memberID  IN(
   SELECT Battles.characterMemberID
   FROM Battles 
   WHERE
   Battles.characterMemberID IN (
    SELECT memberID
    FROM Members
    WHERE expirationDate>='2022-12-10'
   )
   AND
   Battles.monsterID IN (
     SELECT monsterID
     FROM Monsters
     WHERE monsterKind = 'ba'
   ) 
)
AND 
c.role IN(
     SELECT role
     FROM Roles
     WHERE role <> 'knight'
     AND
     c.currentMoney > initialMoney
)
AND
b.characterMemberID = c.memberID
AND
m.monsterID = b.monsterID;
;
