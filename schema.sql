CREATE TABLE IF NOT EXISTS requests (
	card_data text,
	price     integer,
	vendor    text
);

CREATE TABLE IF NOT EXISTS accounts (
	id        serial primary key,
	bank_id   text,
	bank_code text
);
