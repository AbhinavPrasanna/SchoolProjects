CREATE OR REPLACE FUNCTION
increaseSomeThingsCostFunction(maxTotalIncrease INTEGER)
RETURNS INTEGER AS $$


    DECLARE
    	costIncreased	NUMERIC(5,2);	  /* Number actually fired, the value returned */
    	thingsCost NUMERIC(4,2);
        thingCount INTEGER;
        cursorThingID INTEGER;  /* The player to be fired */
        cursorThingKind CHAR(2);
    DECLARE popularCursor CURSOR FOR
    	    SELECT t.thingKind, COUNT(*)
            FROM Things, Characters
            WHERE Things.ownerMemberID IS NOT NULL
              AND Things.ownerRole IS NOT NULL
              AND Characters.memberID = Things.ownerMemberID
              AND Characters.role = Things.ownerRole
            GROUP BY Things.thingKind
            HAVING COUNT(*) >= 3
            ORDER BY COUNT(*) DESC;

    BEGIN

	-- Input Validation
	IF popularCursor <= 0 THEN
	    RETURN -1;		/* Illegal value of maxFired */
	    END IF;

        costIncreased:= 0;

        OPEN cursorThingID;

        LOOP
 
            FETCH cursorThingID INTO thingID;

            -- Exit if there are no more records for firingCursor,
            -- or when we already have performed maxFired firings.
            EXIT WHEN NOT FOUND;
            IF thingCount>=5 and costIncreased + 5 <= maxTotalIncrease THEN
                UPDATE Things 
                SET cost = thingCost + 5
                WHERE thingID = cursorThingID;
            ELSIF thingCount = 4 and costIncreased + 4 <= maxTotalIncrease THEN 
                 UPDATE Things  
                 SET cost = thingCost + 4
                 WHERE thingID = cursorThingID;
            ELSIF thingCount = 3 and costIncreased + 2 <= maxTotalIncrease THEN
                 UPDATE Things  
                 SET cost = thingCost + 2
                 WHERE thingID = cursorThingID;

                 costIncreased:= costIncreased + 2;
            

        END LOOP;
        CLOSE thingCursor;

	RETURN costIncreased;

    END

$$ LANGUAGE plpgsql;
