package com.example.asgn2.models;

import javafx.beans.property.*;

public class ExpiryDetail {
    private final StringProperty expiryDate;
    private final StringProperty stockNo;
    private final IntegerProperty qty;
    private final StringProperty invNo;

    public ExpiryDetail(String expiryDate, String stockNo, int qty, String invNo) {
        this.expiryDate = new SimpleStringProperty(expiryDate);
        this.stockNo = new SimpleStringProperty(stockNo);
        this.qty = new SimpleIntegerProperty(qty);
        this.invNo = new SimpleStringProperty(invNo);
    }

    public String getExpiryDate() { return expiryDate.get(); }
    public StringProperty expiryDateProperty() { return expiryDate; }

    public String getStockNo() { return stockNo.get(); }
    public StringProperty stockNoProperty() { return stockNo; }

    public int getQty() { return qty.get(); }
    public IntegerProperty qtyProperty() { return qty; }

    public String getInvNo() { return invNo.get(); }
    public StringProperty invNoProperty() { return invNo; }
}
