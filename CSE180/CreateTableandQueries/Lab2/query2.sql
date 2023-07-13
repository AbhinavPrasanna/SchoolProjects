SELECT DISTINCT m.name as monsterName 
FROM Monsters m, Battles b 
WHERE m.wasDefeated = FALSE 
AND m.monsterID = b.monsterID 
AND b.monsterBattlePoints < b.characterBattlePoints;