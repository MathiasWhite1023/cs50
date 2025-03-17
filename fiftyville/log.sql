-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.




| Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

people who left the street and called someone at time of the robbery

SELECT people.id, people.name, people.phone_number, people.license_plate
FROM people
WHERE people.license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25
)
AND people.phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE month = 7 AND day = 28
    AND duration < 60
);

+--------+--------+----------------+---------------+
|   id   |  name  |  phone_number  | license_plate |
+--------+--------+----------------+---------------+
| 398010 | Sofia  | (130) 555-0289 | G412CB7       |
| 514354 | Diana  | (770) 555-1861 | 322W7JE       |  514354 account number
| 560886 | Kelsey | (499) 555-9472 | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 94KL13X          26013199


SELECT atm_location FROM atm_transactions WHERE account_number = 26013199 AND month = 7 AND day = 28;
outputs:

+----------------+
|  atm_location  |
+----------------+
| Leggett Street |
+----------------+

thief = Bruce

Calls bruce made:
SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND month = 7 AND day = 28 AND duration < 60;
outputs:
+----------------+
|    receiver    |
+----------------+
| (375) 555-8161 |
+----------------+

SELECT name FROM people WHERE phone_number = '(375) 555-8161';
+-------+
| name  |
+-------+
| Robin |
+-------+

SELECT passport_number FROM people WHERE id = 686048;  ----- Bruce
+-----------------+
| passport_number |
+-----------------+
| 5773159633      |
+-----------------+

SELECT flight_id FROM passengers WHERE passport_number = 5773159633;
+-----------+
| flight_id |
+-----------+
| 36        |
+-----------+

SELECT destination_airport_id FROM flights WHERE id = 36;
+------------------------+
| destination_airport_id |
+------------------------+
| 4                      |
+------------------------+

 SELECT city FROM airports WHERE id = 4;
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
