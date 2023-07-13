SELECT DISTINCT name as memberName,joinDate as memberJoinDate  
FROM Members 
WHERE joinDate IS NOT NULL
AND memberID NOT IN(SELECT ownerMemberID FROM Things  WHERE ownerMemberID = memberID);
