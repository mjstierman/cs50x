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
    user_id INTEGER NOT NULL, 
    date DEFAULT CURRENT_TIMESTAMP NOT NULL, 
    symbol TEXT(6) NOT NULL, 
    price DECIMAL(30, 2) NOT NULL, 
    quantity INT NOT NULL, 
    total DECIMAL(30,2), 
    FOREIGN KEY(user_id) REFERENCES users(id)
    );
CREATE UNIQUE INDEX username ON users (username);
CREATE INDEX date ON records (date);