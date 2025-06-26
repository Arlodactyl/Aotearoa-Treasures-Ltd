
==Aotearoa Treasures Inventory Management System==
#Project by Arleia, Bailey, Oskar

# Overview
The Aotearoa Treasures Inventory Management System is a C++ application developed for Aotearoa Treasures Ltd. It is designed to manage inventory and customer purchases across three store locations: Wellington CBD, Christchurch, and Auckland. The program features separate access modes for Admins and Customers, each with tailored functionality.

#Admin Features (as of 15/06)
#Login using hard-coded credentials (ADMIN / PASSWORD) + STAFF / PASSWORD )
#Browse store products by selecting a store

#Access the Manage Roster submenu:
-Add Staff
-Delete Staff
- Show All Staff Scheduled (displayed in a formatted table)
- Roster Staff Functions (placeholder for future expansion)
- View low-stock alerts for any products with fewer than 5 units
- Return to main menu

#Customer Features 
- Register a new account or sign in using a username and password
- Browse products by store location
- Add products to the cart by selecting product number and quantity
- View the shopping cart, including an itemized list, subtotals, and total
- Purchase products, which updates inventory and tracks user spending
- View spending summary through the account section
- Sign out, which clears the current cart

#Technologies Used
Language: C++
-Development Environment: Visual Studio Community 2022
- Version Control: Git and GitHub
-Project Management: Trello

#Completed Features
Persistent cart functionality was implemented using a global vector to allow users to accumulate multiple items before checkout. The purchaseCart function deducts purchased items from stock, calculates the total price, updates the user’s cumulative spend, and then clears the cart.
#Store searching is supported through a keyword-based search function within each store's inventory. After logging in, users can view a summary of their total spending using the viewSummary function.
#Admins can access a Low Stock Alerts option to identify items with stock levels below five. All input values are validated to prevent negative or zero quantities. Age input during user registration is also validated to be within a logical range (5 to 120).

#Completed Task List
-Cart supports multiple items (completed by Arleia)
-Users can purchase products and update store inventory
-Search function allows keyword-based queries within a store
-Users can view a summary of their total spending
- Admin panel includes a stock notification system
- Input validation prevents negative or invalid entries

#Final Notes
The system is now fully functional with all core features implemented. The team has completed all originally planned tasks and is satisfied with the outcome. Future updates could include expanded account details and payment gateway.


