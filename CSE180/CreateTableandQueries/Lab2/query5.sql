SELECT DISTINCT eastRoom.roomID AS eastRoomID, 
eastRoom.roomDescription AS eastRoomDescription, 
westRoom.roomID AS westRoomId, 
westRoom.roomDescription AS westRoomDescription 
FROM Rooms AS eastRoom, 
Rooms AS westRoom
WHERE eastRoom.roomID = westRoom.westNext AND eastRoom.eastNext = westRoom.roomID; 