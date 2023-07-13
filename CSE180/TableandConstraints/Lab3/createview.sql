CREATE VIEW FullBattlePointsView(memberID,role,name,fullBattlePoints) AS 
    SELECT Characters.memberID, Characters.role, Characters.name, Roles.battlePoints + Things.extraBattlePoints
    FROM Characters, Things, Roles
    WHERE
    Characters.memberID = Things.ownerMemberID
    AND
    Characters.role = Roles.role 
    AND 
    Things.ownerRole = Characters.role;