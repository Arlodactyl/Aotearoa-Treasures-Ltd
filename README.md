# Aotearoa Treasures Inventory Management System
## Project by Arleia, Bailey, Oskar
## Overview

This repository contains the source code for the **Aotearoa Treasures Inventory Management System**, a C++ application developed for Aotearoa Treasures Ltd. The system is designed to help manage inventory levels and customer purchases across three physical stores: Wellington CBD, Christchurch, and Auckland.

---

## Features

### Admin Functionality
- View inventory levels across all stores
- See alerts for items with fewer than five units in stock
- Add, edit, or delete products


### Customer Functionality
- Select a store to shop from
- View available products
- Make purchases (automatically updates store-specific inventory)

---

## Technologies Used

- **Language:** C++
- **Development Tools:** Visual Studio Community 2022
- **Version Control:** Git & GitHub
- **Project Management:** Trello

---

## Todo

- Add a cart for user and its able to store multiple purchases (DONE - ARLEIA)
- User is able to purchase a product from the store
- User is able to search for a product within the selected store, exp.(Search function in [Struct] store)
- User is able to view a summary of there spending, exp.(view summary function in [Struct] User)
- Add a notifaction feature inside admin menu (To see all stock below values of 5)
- System shouldn't be able to see any negative values
  
- Bailey - "I think thats all thats left really, can discuss on Monday"
----- Arleia 
- Persistent cart with multiple items
The global vector<CartItem> cart plus addToCart() lets a user accumulate as many different products (and quantities) as they like before checkout.
Purchasing products
purchaseCart() deducts each item from stock, totals up the price, records it in the current user’s totalSpent, and clears the cart.
In-store search
Store::searchProducts(keyword) scans the selected store’s product list and displays any matches.
Viewing spending summary
After login you can choose “Account” to call User::viewSummary(), which prints the user’s cumulative spend.
Admin low-stock notifications
In the Admin Panel, option 3 “Low Stock Alerts” walks every store’s inventory and lists anything below 5 units.
No negative inputs
addToCart() rejects zero or negative quantities.
User::getInformation() validates age to be between 5 and 120.
purchaseCart() checks available stock before deducting so you can’t go negative.









