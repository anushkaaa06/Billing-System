# 💳 Billing System in C++

A simple yet powerful console-based Billing System developed in C++ using object-oriented programming. This system allows both **customers** and **administrators** to interact with product data, generate invoices, and manage billing operations with ease.

## 🛠️ Features

### 🔐 Admin Module
- Add new products with product number, name, and rate
- View all available products
- Modify existing product rates
- Delete products from the system

### 🛒 Customer Billing Interface
- View available products
- Select products and enter quantity
- Auto-generate a detailed invoice with:
  - Item-wise breakdown
  - Quantity × Rate
  - Total amount
  - Date & Time of purchase

### 📄 File Handling
- All products are stored in a file: `Products.txt`
- File is read and updated dynamically as per admin actions

### 👨‍💻 Object-Oriented Design
The project uses modular class-based architecture:
- `Product`
- `Bill`
- `BillItems`
- `Invoice`

## 🧱 Tech Stack

- **Language:** C++  
- **Compiler:** GCC / g++  
- **Concepts Used:** File Handling, OOP, Classes & Inheritance, CLI Menu Navigation
