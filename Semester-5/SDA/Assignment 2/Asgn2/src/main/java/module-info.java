module com.example.asgn2 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires net.synedra.validatorfx;
    requires org.kordamp.ikonli.javafx;
    requires org.kordamp.bootstrapfx.core;
    requires org.jetbrains.annotations;
    requires java.desktop;

    opens com.example.asgn2 to javafx.fxml;
    opens com.example.asgn2.models to javafx.base;  // 🔑 allow TableView to access getters
    exports com.example.asgn2;
    exports com.example.asgn2.models;
}