package com.example.asgn2.models;

import javafx.beans.property.*;

public class StockItem {
    private final StringProperty stockNo;
    private final StringProperty brandName;
    private final StringProperty type;

    public StockItem(String stockNo, String brandName, String type) {
        this.stockNo = new SimpleStringProperty(stockNo);
        this.brandName = new SimpleStringProperty(brandName);
        this.type = new SimpleStringProperty(type);
    }

    public String getStockNo() { return stockNo.get(); }
    public StringProperty stockNoProperty() { return stockNo; }

    public String getBrandName() { return brandName.get(); }
    public StringProperty brandNameProperty() { return brandName; }

    public String getType() { return type.get(); }
    public StringProperty typeProperty() { return type; }
}
