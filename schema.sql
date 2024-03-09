CREATE TABLE IF NOT EXISTS accounts (
	id        serial primary key,
	bank_id   text,
	bank_code text
);

CREATE TABLE IF NOT EXISTS requests (
	from_id   integer REFERENCES accounts(id),
	to_id     integer REFERENCES accounts(id),
	amount    text,
	is_credit boolean
);
