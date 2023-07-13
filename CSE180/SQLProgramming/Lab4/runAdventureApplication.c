/**
 * runAdventureApplication skeleton, to be modified by students
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libpq-fe.h"

/* These constants would normally be in a header file */
/* Maximum length of string used to submit a connection */
#define MAXCONNECTIONSTRINGSIZE 501
/* Maximum length of string used to submit a SQL statement */
#define MAXSQLSTATEMENTSTRINGSIZE 2001
/* Maximum length of string version of integer; you don't have to use a value this big */
#define  MAXNUMBERSTRINGSIZE        20


/* Exit with success after closing connection to the server
 *  and freeing memory that was used by the PGconn object.
 */
static void good_exit(PGconn *conn)
{
    PQfinish(conn);
    exit(EXIT_SUCCESS);
}

/* Exit with failure after closing connection to the server
 *  and freeing memory that was used by the PGconn object.
 */
static void bad_exit(PGconn *conn)
{
    PQfinish(conn);
    exit(EXIT_FAILURE);
}

/* The three C functions that for Lab4 should appear below.
 * Write those functions, as described in Lab4 Section 4 (and Section 5,
 * which describes the Stored Function used by the third C function).
 *
 * Write the tests of those function in main, as described in Section 6
 * of Lab4.
 */

/* Function: printNumberOfThingsInRoom:
 * -------------------------------------
 * Parameters:  connection, and theRoomID, which should be the roomID of a room.
 * Prints theRoomID, and number of things in that room.
 * Return 0 if normal execution, -1 if no such room.
 * bad_exit if SQL statement execution fails.
 */


int printNumberOfThingsInRoom(PGconn *conn, int theRoomID)
{
   char value[256];
   sprintf(value, "SELECT roomID,roomDescription FROM Rooms WHERE roomID = %d", theRoomID);
   PGresult *begin = PQexec(conn,value);
   if (PQresultStatus(begin) != PGRES_TUPLES_OK)
    {

        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(begin);
        bad_exit(conn);

    }
   char value2[256];
   sprintf(value2,"SELECT Things.thingID FROM Things, Characters WHERE Things.ownerRole = Characters.role AND Things.ownerMemberID = Characters.memberID AND Characters.roomID = %d UNION SELECT Things.thingID FROM Things WHERE Things.ownerMemberID IS NULL AND Things.initialRoomID = %d",theRoomID,theRoomID);
   PGresult *result = PQexec(conn,value2);
   if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {

        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(result);
        bad_exit(conn);

    }
   int numofthings = PQntuples(result);
   int numrooms = PQntuples(begin);
   if(numrooms>0){
      printf("Room %s,%s, has %d in it",PQgetvalue(begin,0,0),PQgetvalue(begin,0,1),numofthings);
      return 0;
   }
   return -1;
}
/* Function: updateWasDefeated:
 * ----------------------------
 * Parameters:  connection, and a string, doCharactersOrMonsters, which should be 'C' or 'M'.
 * Updates the wasDefeated value of either characters or monsters (depending on value of
 * doCharactersOrMonsters) if that value is not correct.
 * Returns number of characters or monsters whose wasDefeated value was updated,
 * or -1 if doCharactersOrMonsters value is invalid.
 */

int updateWasDefeated(PGconn *conn, char *doCharactersOrMonsters)
{
  if (strcmp(doCharactersOrMonsters,"C")!=0 && strcmp(doCharactersOrMonsters,"M")!=0){
        printf("ERROR!\n");
        return -1;
    }
    int wrongvalues = 0;
    if (strcmp(doCharactersOrMonsters,"C")==0)
    {
      PGresult *result = PQexec(conn,"UPDATE Characters SET wasDefeated = TRUE FROM Battles WHERE Battles.characterMemberID = Characters.memberID AND Battles.characterRole = Characters.role AND Battles.characterBattlePoints < Battles.monsterBattlePoints RETURNING Characters.*");
      wrongvalues += PQntuples(result);
      result = PQexec(conn,"UPDATE Characters SET wasDefeated = FALSE FROM Battles WHERE Battles.characterMemberID = Characters.memberID AND Battles.characterRole = Characters.role AND Battles.characterBattlePoints > Battles.monsterBattlePoints");
      wrongvalues += PQntuples(result);
    }
    else
    {
      PGresult *result = PQexec(conn,"UPDATE Monsters SET wasDefeated=TRUE FROM Battles WHERE Battles.monsterID = Monsters.monsterID AND Battles.monsterBattlePoints<Battles.characterBattlePoints RETURNING Monsters.*");
      wrongvalues += PQntuples(result);
      result = PQexec(conn,"UPDATE Monsters SET wasDefeated=FALSE FROM Battles WHERE Battles.monsterID = Monsters.monsterID AND Battles.monsterBattlePoints>Battles.characterBattlePoints RETURNING Monsters.*");
      wrongvalues += PQntuples(result);
    }
    return wrongvalues;
}

/* Function: increaseSomeThingCosts:
 * -------------------------------
 * Parameters:  connection, and an integer maxTotalIncrease, the maximum total increase that
 * it should make in the cost of some things.
 * Executes by invoking a Stored Function, increaseSomeThingCostsFunction, which
 * returns a negative value if there is an error, and otherwise returns the total
 * cost increase that was performed by the Stored Function.
 */

int increaseSomeThingCosts(PGconn *conn, int maxTotalIncrease)
{
    
}

int main(int argc, char **argv)
{
    PGconn *conn;
    int theResult;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./runAdventureApplication <username> <password>\n");
        exit(EXIT_FAILURE);
    }

    char *userID = argv[1];
    char *pwd = argv[2];

    char conninfo[MAXCONNECTIONSTRINGSIZE] = "host=cse180-db.lt.ucsc.edu user=";
    strcat(conninfo, userID);
    strcat(conninfo, " password=");
    strcat(conninfo, pwd);

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);

    /* Check to see if the database connection was successfully made. */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));
        bad_exit(conn);
    }

    int result;
    printNumberOfThingsInRoom(conn, 1);
    printNumberOfThingsInRoom(conn, 2);
    printNumberOfThingsInRoom(conn,3);
    printNumberOfThingsInRoom(conn,7);
    printNumberOfThingsInRoom(conn,-1);
    /* Perform the calls to printNumberOfThingsInRoom listed in Section 6 of Lab4,
     * printing error message if there's an error.
     */
    
    /* Extra newline for readability */
    printf("\n");

    
    /* Perform the calls to updateWasDefeated listed in Section 6 of Lab4,
     * and print messages as described.
     */
    
    /* Extra newline for readability */
    updateWasDefeated(conn,"C");
    updateWasDefeated(conn,"M");
    updateWasDefeated(conn,"C");
    updateWasDefeated(conn,"S");
    printf("\n");

    
    /* Perform the calls to increaseSomeThingCosts listed in Section 6 of Lab4,
     * and print messages as described.
     */
    increaseSomeThingCosts(conn,1);
    increaseSomeThingCosts(conn,500);
    increaseSomeThingCosts(conn,39);
    increaseSomeThingCosts(conn,1);
    good_exit(conn);
    return 0;
}
