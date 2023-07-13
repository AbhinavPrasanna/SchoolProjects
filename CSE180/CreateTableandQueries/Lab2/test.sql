SELECT DISTINCT R1.roomID AS eastRoomID, R1.roomDescription AS eastRoomDescription, R2.roomID AS westRoomId, R2.roomDescription AS westRoomDescription FROM Rooms AS R1, Rooms AS R2
WHERE R1.roomID = R2.westNext AND R1.eastNext = R2.roomID; 