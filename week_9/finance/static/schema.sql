CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    username TEXT NOT NULL, 
    hash TEXT NOT NULL, 
    cash NUMERIC NOT NULL DEFAULT 10000.00
);
CREATE TABLE sqlite_sequence(
    name,
    seq
);
CREATE TABLE records (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    FOREIGN KEY (user_id) REFERENCES users(id) NOT NULL,
    date DATETIME DEFAULT ON UPDATE NOT NULL,
    symbol TEXT(4) NOT NULL,
    price DECIMAL(2, 30) NOT NULL,
    quantity INT NOT NULL,
);
CREATE UNIQUE INDEX username ON users (username);
CREATE UNIQUE INDEX records ON records (id);
CREATE INDEX date ON records (date);
