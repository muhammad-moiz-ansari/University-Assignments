package com.example.asgn2.models;

import javafx.beans.property.*;

public class MedicineItem {
    private final StringProperty stockNo;
    private final StringProperty brandName;
    private final StringProperty medicineType;
    private final IntegerProperty quantity;
    private final DoubleProperty price;
    private final DoubleProperty amount;

    public MedicineItem(String stockNo, String brandName, String medicineType, int quantity, double price, double amount) {
        this.stockNo = new SimpleStringProperty(stockNo);
        this.brandName = new SimpleStringProperty(brandName);
        this.medicineType = new SimpleStringProperty(medicineType);
        this.quantity = new SimpleIntegerProperty(quantity);
        this.price = new SimpleDoubleProperty(price);
        this.amount = new SimpleDoubleProperty(amount);
    }

    public String getStockNo() { return stockNo.get(); }
    public StringProperty stockNoProperty() { return stockNo; }

    public String getBrandName() { return brandName.get(); }
    public StringProperty brandNameProperty() { return brandName; }

    public String getMedicineType() { return medicineType.get(); }
    public StringProperty medicineTypeProperty() { return medicineType; }

    public int getQuantity() { return quantity.get(); }
    public IntegerProperty quantityProperty() { return quantity; }

    public double getPrice() { return price.get(); }
    public DoubleProperty priceProperty() { return price; }

    public double getAmount() { return amount.get(); }
    public DoubleProperty amountProperty() { return amount; }
}
