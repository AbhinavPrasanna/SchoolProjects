--Script to populate the Adventure schema for F11 CSE 180 Lab1


-- Members(memberID, name, address, joinDate, expirationDate, isCurrent)
COPY Members FROM stdin USING DELIMITERS '|';
101|\N|123 Main St, New York, NY|2018-01-09|2022-01-09|FALSE
120|Tom Johnson|333 Meder Dr, St. Paul, MN|2011-03-21|2023-04-21|TRUE
103|Siobhan Roy|9931 El Camino, New York, NY|\N|2022-12-16|TRUE
104|Greg Hirsch|831 Santa Cruz Ave, Toronto, ON|\N|2024-03-15|TRUE
111|Roman Chan|123 Main St, New York, NY|2018-12-17|\N|TRUE
109|Gerri Kellman|222 Emmet Grade, Newark, NJ|2016-07-31|2023-06-02|TRUE
131|\N|11 Private Dr, New York, NY|2022-01-04|2022-12-28|TRUE
100|Logan Schwartz|101 W34 St, New York, NY|2018-05-16|2024-05-16|FALSE
143|Tom Johnson|101 W34 St, New York, NY|\N|2030-02-17|FALSE
99|Greg Hirsch|\N|2016-07-31|2018-12-31|TRUE
165|Greg Hirsch|101 W34 St, New York, NY|2013-11-01|2027-07-01|TRUE
102|Greg Hirsch|\N|\N|2024-09-18|TRUE
\.

-- Rooms(roomID, roomDescription, northNext, eastNext, southNext, westNext)
COPY Rooms FROM stdin USING DELIMITERS '|';
1|Hall of Mountain King|2|5|4|3
2|Witts End|\N|\N|1|\N
3|Twopit Room|\N|1|6|5
4|Misty Cavern|1|\N|\N|6
5|Barren Room|\N|3|\N|1
6|Twilight Genics|3|4|\N|\N
\.

-- Roles(role, battlePoints, InitialMoney)
COPY Roles FROM stdin USING DELIMITERS '|';
knight|30|62.34
mage|129|95.11
cleric|203|48.97
rogue|169|150.00
\.

-- Characters(memberID, role, name, roomID, currentMoney, wasDefeated)
COPY Characters FROM stdin USING DELIMITERS '|';
101|knight|Lancelot|1|62.34|FALSE
99|mage|Oliver|4|123.69|TRUE
111|cleric|Patrick|1|48.97|FALSE
165|rogue|\N|4|165.00|TRUE
101|mage|Merlin|3|82.34|FALSE
100|knight|Galahad|2|55.11|FALSE
101|rogue|Bilbo|3|100.25|TRUE
103|mage|Morgan|3|95.15|TRUE
165|cleric|Michael|1|48.97|TRUE
99|cleric|\N|4|66.08|TRUE
143|cleric|Jack|6|75.48|TRUE
103|rogue|Noah|6|150.00|TRUE
102|cleric|Benjamin|1|48.97|TRUE
165|knight|Mateo|2|23.48|TRUE
102|rogue|Lucas|3|150.00|TRUE
143|mage|\N|4|95.11|TRUE
165|mage|Levi|6|95.11|TRUE
102|knight|Henry|1|156.81|TRUE
\.

-- Things(thingID, thingKind, initialRoomID, ownerMemberID, ownerRole, cost, extraBattlePoints)
COPY Things FROM stdin USING DELIMITERS '|';
6002|sc|1|\N|\N|7.32|5
6049|sw|3|101|knight|20.25|18
6075|sh|5|111|cleric|14.99|12
6034|sc|3|101|mage|8.42|8
6021|ma|2|\N|\N|9.00|6
6014|sc|3|101|knight|5.55|8
6023|sc|6|\N|\N|18.00|8
6005|st|4|101|rogue|17.76|10
6006|sc|3|\N|\N|11.39|17
\.

-- Monsters(monsterID, monsterKind, name, battlePoints, roomID, wasDefeated)
COPY Monsters FROM stdin USING DELIMITERS '|';
944|ba|Unfriendly Giant|202|5|FALSE
963|ch|Bob|24|3|TRUE
965|ba|\N|0|4|FALSE
925|gi|Fee Fie|213|3|FALSE
988|\N|Bullseye|0|1|FALSE
971|ga|Gargamel|24|2|TRUE
972|\N|Bullseye|64|5|FALSE
923|ba|Gargamel|46|3|FALSE
942|mi|Bane|0|5|FALSE
956|ba|\N|21|4|FALSE
\.

-- Battles(characterMemberID, characterRole, characterBattlePoints, monsterID, monsterBattlePoints)
COPY Battles FROM stdin USING DELIMITERS '|';
101|knight|30|963|24
99|cleric|25|925|46
101|rogue|20|944|72
103|mage|27|944|41
111|cleric|13|925|55
165|rogue|77|923|46
102|cleric|67|972|64
165|rogue|39|971|24
103|mage|102|925|112
102|cleric|98|944|89
165|rogue|29|956|21
\.
