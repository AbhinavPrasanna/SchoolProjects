CREATE TABLE Members(memberID INT PRIMARY KEY,name VARCHAR(50),address VARCHAR(50),joinDate DATE,expirationDate DATE,isCurrent BOOLEAN, UNIQUE(name,address));

CREATE TABLE Rooms(roomID INT PRIMARY KEY, roomDescription VARCHAR(30) NOT NULL, northNext INT REFERENCES Rooms(roomID) , eastNext INT REFERENCES Rooms(roomID),southNext INT REFERENCES Rooms(roomID),westNext INT REFERENCES Rooms(roomID));

CREATE TABLE Roles(role VARCHAR(6) PRIMARY KEY,battlePoints INT,initialMoney NUMERIC(5,2));

CREATE TABLE Characters(memberID INT, role VARCHAR(6), name VARCHAR(50) UNIQUE, roomID INT NOT NULL, currentMoney NUMERIC(5,2), wasDefeated BOOLEAN, FOREIGN KEY(memberID) REFERENCES Members(memberID), FOREIGN KEY(role) REFERENCES Roles(role), FOREIGN KEY(roomID) REFERENCES Rooms(roomID), PRIMARY KEY(memberID,role));

CREATE TABLE Things(thingID INT PRIMARY KEY, thingKind CHAR(2), initialRoomID INT, ownerMemberID INT, ownerRole VARCHAR(6), cost NUMERIC(4,2) NOT NULL, extraBattlePoints INT, FOREIGN KEY(initialRoomID) REFERENCES Rooms(roomID), FOREIGN KEY(ownerMemberID,ownerRole) REFERENCES Characters(memberID,role));

CREATE TABLE Monsters(monsterID INT PRIMARY KEY, monsterKind CHAR(2), name VARCHAR(50), battlePoints INT, roomID INT, wasDefeated BOOLEAN, FOREIGN KEY(roomID) REFERENCES Rooms(roomID), UNIQUE(monsterKind,name));

CREATE TABLE Battles(characterMemberID INT, characterRole  VARCHAR(6), characterBattlePoints INT, monsterID INT, monsterBattlePoints INT, FOREIGN KEY(characterMemberID, characterRole) REFERENCES Characters(memberID,role), FOREIGN KEY(monsterID) REFERENCES Monsters(monsterID),PRIMARY KEY(characterMemberID,characterRole,monsterID));
