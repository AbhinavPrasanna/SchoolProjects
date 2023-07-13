SELECT DISTINCT r.roomID, r.roomDescription,t.thingID, t.cost 
FROM Things t, Rooms r 
WHERE t.thingKind = 'sc' 
AND r.roomID = t.initialRoomID 
AND r.roomDescription LIKE '_w%' 
AND t.cost<12 
ORDER BY r.roomDescription ASC, t.cost DESC;