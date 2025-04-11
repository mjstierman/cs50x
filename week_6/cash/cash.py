""" A module to return how many coins to give back to an over-paying customer """

def get_int(ask) -> int:
    """ Query the user for an int """
    out = int(input(ask))
    return out

def calc_change(payment) -> int:
    """ return the change owed in dollars """
    price = 50
    change = payment - price
    return change

def calc_coins(change) -> int:
    """ calculate the number of coins returned """
    coin_count = 0
    while change > 24:
        change -= 25
        coin_count += 1
    while change > 9:
        change -= 10
        coin_count += 1
    while change > 4:
        change -= 5
        coin_count += 1
    while change > 0:
        change -= 1
        coin_count += 1
    return coin_count

def main():
    """ Do the needful """
    paid = get_int("How much was paid (in cents)? ")
    change = calc_change(paid)
    coinage = calc_coins(change)
    print(f"Change owned: {change}")
    print(f"Number of Coins: {coinage}")

main()
