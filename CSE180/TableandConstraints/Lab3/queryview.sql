SELECT FullBattlePointsView.memberID as theMemberID, FullBattlePointsView.role as theRole, FullBattlePointsView.name as theName, SUM(FullBattlePointsView.fullBattlePoints) as theFullBattlePoints, COUNT(*) as numLosses
FROM FullBattlePointsView, Battles, Characters
WHERE Battles.monsterBattlePoints > Battles.characterBattlePoints
AND
Battles.characterMemberID = Characters.memberID
AND
Characters.wasDefeated = FALSE
GROUP BY(theMemberID, theRole, theName)
HAVING COUNT(*) >=3 and FullBattlePointsView.name IS NOT NULL;

--  First table before deletion
-- thememberid | therole | thename  | thefullbattlepoints | numlosses 
-- -------------+---------+----------+---------------------+-----------
--          165 | rogue   | Oliver   |               12172 |        68
--          101 | rogue   | Jack     |                6086 |        34
--          111 | cleric  | Patrick  |                7310 |        34
--          101 | mage    | Jack     |                4658 |        34
--          101 | knight  | Lancelot |                2924 |        68
-- (5 rows)

DELETE FROM Battles
    WHERE characterMemberID = 111
    AND characterRole = 'cleric'
    AND monsterID = 925;

DELETE FROM Battles 
    WHERE characterMemberID = 101
    AND characterRole = 'knight'
    AND monsterID = 944;

--  Second Table
-- thememberid | therole | thename  | thefullbattlepoints | numlosses 
-- -------------+---------+----------+---------------------+-----------
--          165 | rogue   | Oliver   |               10740 |        60
--          101 | rogue   | Jack     |                5370 |        30
--          111 | cleric  | Patrick  |                6450 |        30
--          101 | mage    | Jack     |                4110 |        30
--          101 | knight  | Lancelot |                2580 |        60
-- (5 rows)