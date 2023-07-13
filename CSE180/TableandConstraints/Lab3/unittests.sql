INSERT INTO Battles(characterMemberID,characterRole,monsterID)
    VALUES(134567,'ba',13456);

INSERT INTO Battles(characterMemberID,characterRole,monsterID)
    VALUES(234567,'ba',345678);

INSERT INTO Things(thingID,ownerMemberID,ownerRole)
    VALUES(1214321431,1212414132,'ba');

UPDATE Things
    SET cost = -1
    WHERE cost >= 0;

UPDATE Things
    SET cost = 2
    WHERE thingID=3;

UPDATE Monsters
    SET monsterKind = 'ba'
    WHERE battlePoints >= 42;

UPDATE Monsters
    SET  monsterKind = 'ch'
    WHERE battlePoints >= 42;

UPDATE Members
    SET  isCurrent = NULL
    WHERE expirationDate = NULL;

UPDATE Members
    SET isCurrent = CURRENT_DATE
    WHERE expirationDate = NULL;
