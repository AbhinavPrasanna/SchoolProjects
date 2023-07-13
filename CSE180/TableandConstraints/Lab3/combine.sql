BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;

INSERT INTO Members
        SELECT ModifyMembers.memberID, ModifyMembers.name, ModifyMembers.address, CURRENT_DATE, ModifyMembers.expirationDate, NULL
        FROM ModifyMembers 
        WHERE ModifyMembers.memberID NOT IN(SELECT memberID
                                            FROM Members);

    UPDATE Members 
    SET name = m1.name,
    address = m1.address,
    expirationDate = m1.expirationDate,
    isCurrent = TRUE
    FROM ModifyMembers m1
    WHERE Members.memberID = m1.memberID;

COMMIT;








