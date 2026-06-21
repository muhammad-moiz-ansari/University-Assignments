package com.example.asgn2;

import javafx.beans.binding.Bindings;
import javafx.fxml.FXML;
import com.example.asgn2.models.MedicineItem;
import com.example.asgn2.models.StockItem;
import com.example.asgn2.models.ExpiryDetail;

import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import javafx.scene.control.Label;
import javafx.scene.control.Button;
import javafx.beans.binding.Bindings;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.util.Objects;

public class HelloController {
    @FXML private Label medicineCountLabel;
    @FXML private Button printButton;

    @FXML private TableView<MedicineItem> medicineTable;
    @FXML private TableColumn<MedicineItem, String> colStockNo;
    @FXML private TableColumn<MedicineItem, String> colBrandName;
    @FXML private TableColumn<MedicineItem, String> colMedicineType;
    @FXML private TableColumn<MedicineItem, Integer> colQuantity;
    @FXML private TableColumn<MedicineItem, Double> colPrice;
    @FXML private TableColumn<MedicineItem, Double> colAmount;

    @FXML private TableView<StockItem> stockTable;
    @FXML private TableColumn<StockItem, String> colStockNo2;
    @FXML private TableColumn<StockItem, String> colBrandName2;
    @FXML private TableColumn<StockItem, String> colType;

    @FXML private TableView<ExpiryDetail> expiryTable;
    @FXML private TableColumn<ExpiryDetail, String> colExpiryDate;
    @FXML private TableColumn<ExpiryDetail, String> colStockNo3;
    @FXML private TableColumn<ExpiryDetail, Integer> colQty;
    @FXML private TableColumn<ExpiryDetail, String> colInvNo;

    @FXML
    private void onPrintButtonClick() {
        // Load the image
        Image image = new Image(Objects.requireNonNull(getClass().getResource("receipt.png")).toExternalForm());
        ImageView imageView = new ImageView(image);

        // Adjust image size if needed
        imageView.setFitWidth(300);
        imageView.setPreserveRatio(true);

        // Create layout and scene
        StackPane pane = new StackPane(imageView);
        Scene scene = new Scene(pane, 350, 250);

        // Create a new small Stage
        Stage popupStage = new Stage();
        popupStage.setTitle("Print Receipt");
        popupStage.setScene(scene);
        popupStage.show();
    }

    @FXML
    public void initialize() {
        // Medicine Table
        colStockNo.setCellValueFactory(new PropertyValueFactory<>("stockNo"));
        colBrandName.setCellValueFactory(new PropertyValueFactory<>("brandName"));
        colMedicineType.setCellValueFactory(new PropertyValueFactory<>("medicineType"));
        colQuantity.setCellValueFactory(new PropertyValueFactory<>("quantity"));
        colPrice.setCellValueFactory(new PropertyValueFactory<>("price"));
        colAmount.setCellValueFactory(new PropertyValueFactory<>("amount"));

        medicineTable.getItems().add(new MedicineItem("3902850", "CEDROX 1G 10S", "Tablet", 4, 28.34, 113.36));
        medicineTable.getItems().add(new MedicineItem("2309823", "PANADOL 10G 20S", "Tablet", 3, 100.00, 300.00));
        medicineTable.getItems().add(new MedicineItem("4036742", "ALLIUM CEPA 200", "Drops", 1, 799.99, 799.99));

        // Bind label to number of rows in medicineTable
        medicineCountLabel.textProperty().bind(
                Bindings.size(medicineTable.getItems()).asString("%d")
        );

        // Stock Table
        colStockNo2.setCellValueFactory(new PropertyValueFactory<>("stockNo"));
        colBrandName2.setCellValueFactory(new PropertyValueFactory<>("brandName"));
        colType.setCellValueFactory(new PropertyValueFactory<>("type"));

        stockTable.getItems().add(new StockItem("3902974", "PANADOL SYRUP 100ML 1S", "Liquid"));
        stockTable.getItems().add(new StockItem("3902987", "PANADOL DROP 15ML 1S", "Liquid"));
        stockTable.getItems().add(new StockItem("3902956", "PANADOL TAB 500MG 10S", "Tablet"));
        stockTable.getItems().add(new StockItem("3902874", "PANADOL EXTRA 500MG 10S", "Tablet"));

        // Expiry Table
        colExpiryDate.setCellValueFactory(new PropertyValueFactory<>("expiryDate"));
        colStockNo3.setCellValueFactory(new PropertyValueFactory<>("stockNo"));
        colQty.setCellValueFactory(new PropertyValueFactory<>("qty"));
        colInvNo.setCellValueFactory(new PropertyValueFactory<>("invNo"));

        expiryTable.getItems().add(new ExpiryDetail("3/3/2018", "3903400", 11752, "16"));
    }
}
