-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Read the Crime Scene Report from when and where the crime took place
SELECT description FROM crime_scene_reports WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Read the Interviews from that day
SELECT name,transcript FROM interviews WHERE year = 2024 AND month = 7 AND day = 28;

-- Follow the leads
--
-- First, a record of the cars leaving the bakery between 10:15 and 10:25
SELECT license_plate,hour,minute FROM bakery_security_logs WHERE activity = 'exit' AND year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;
-- Look up the plates, get the owners name and passport number
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE activity = 'exit' AND year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25);

-- When did Eugene arrive at the bakery?
SELECT hour,minute FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2024 AND license_plate IN (SELECT license_plate FROM people WHERE name = 'Eugene');
-- He didn't...
-- ATM records:
SELECT * from atm_transactions WHERE month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street';
-- Get the names of the owners:
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number from atm_transactions WHERE transaction_type = 'withdraw' AND month = 7 AND day = 28 AND year = 2024 AND atm_location = 'Leggett Street'));

-- Phone calls from 7/28 less than a minute:
SELECT * FROM phone_calls WHERE duration < 60 AND month = 7 AND day = 28 AND year = 2024;
-- Who called whom? We need to make two joins and use aliases
SELECT p1.name AS caller_name, p2.name AS receiver_name FROM phone_calls JOIN people p1 ON phone_calls.caller = p1.phone_number JOIN people p2 ON phone_calls.receiver = p2.phone_number WHERE    phone_calls.duration < 60 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.year = 2024;

-- What is the earliest flight out of Fiftyville?
SELECT * FROM flights WHERE month = 7 AND day = 29 AND year = 2024 ORDER BY hour ASC LIMIT 1;
-- Where is it going?
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE month = 7 AND day = 29 AND year = 2024 ORDER BY hour ASC LIMIT 1);
-- And who bought tickets for that flight:
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 AND year = 2024 ORDER BY hour ASC LIMIT 1));

-- Bruce is the only name to appear in all searches. Bruce called Robin for help, then flew to NYC the next day.