# Simon Fraser Credit Union

## Backend Routine

- Run `ret = dns_check()` every 5 minutes or so.
  - `for (int i = 0; i < ret; i++)`:
    - `req = dns_request()`
      - Contains fields 

## Database

The database is interacted with using `psql`.

Ensure that the database `sfcu` exists.
You can create it with `createdb sfcu`.

To check that the database is working, run `sfcu -d sfcu -c "\d"`.
It should give a description of all relations existing in the database.

Make sure that you run the `sfcu` program using the user that is able to run the above command.

### Setup

To setup the server, run `psql -d sfcu -f schema.sql`.
`schema.sql` contains SQL commands that will set up all relations needed to run the `sfcu` program.
