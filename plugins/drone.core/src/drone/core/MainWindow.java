package drone.core;
/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
**
** This file is part of Qt Jambi.
**
** $JAVA_LICENSE$
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/


import com.trolltech.qt.core.*;
import com.trolltech.qt.gui.*;

public class MainWindow extends QWidget {

    private QLineEdit echoLineEdit;
    private QLineEdit validatorLineEdit;
    private QLineEdit alignmentLineEdit;
    private QLineEdit inputMaskLineEdit;
    private QLineEdit accessLineEdit;

    public MainWindow() {
	QGroupBox echoGroup = new QGroupBox(tr("Echo"));

	QLabel echoLabel = new QLabel(tr("Mode:"));
	QComboBox echoComboBox = new QComboBox();
	echoComboBox.addItem(tr("Normal"));
	echoComboBox.addItem(tr("Password"));
	echoComboBox.addItem(tr("No Echo"));
    
    setWindowIcon(new QIcon("classpath:com/trolltech/images/qt-logo.png"));

	echoLineEdit = new QLineEdit();
	echoLineEdit.setFocus();

	QGroupBox validatorGroup = new QGroupBox(tr("Validator"));

	QLabel validatorLabel = new QLabel(tr("Type:"));
	QComboBox validatorComboBox = new QComboBox();
	validatorComboBox.addItem(tr("No validator"));
	validatorComboBox.addItem(tr("Integer validator"));
	validatorComboBox.addItem(tr("Double validator"));

	validatorLineEdit = new QLineEdit();

	QGroupBox alignmentGroup = new QGroupBox(tr("Alignment"));

	QLabel alignmentLabel = new QLabel(tr("Type:"));
	QComboBox alignmentComboBox = new QComboBox();
	alignmentComboBox.addItem(tr("Left"));
	alignmentComboBox.addItem(tr("Centered"));
	alignmentComboBox.addItem(tr("Right"));

	alignmentLineEdit = new QLineEdit();

	QGroupBox inputMaskGroup = new QGroupBox(tr("Input mask"));

	QLabel inputMaskLabel = new QLabel(tr("Type:"));
	QComboBox inputMaskComboBox = new QComboBox();
	inputMaskComboBox.addItem(tr("No mask"));
	inputMaskComboBox.addItem(tr("Phone number"));
	inputMaskComboBox.addItem(tr("ISO date"));
	inputMaskComboBox.addItem(tr("License key"));

	inputMaskLineEdit = new QLineEdit();

	QGroupBox accessGroup = new QGroupBox(tr("Access"));

	QLabel accessLabel = new QLabel(tr("Read-only:"));
	QComboBox accessComboBox = new QComboBox();
	accessComboBox.addItem(tr("False"));
	accessComboBox.addItem(tr("True"));

	accessLineEdit = new QLineEdit();

	echoComboBox.activatedIndex.connect(this, "echoChanged(int)");
	validatorComboBox.activatedIndex.connect(this, "validatorChanged(int)");
	alignmentComboBox.activatedIndex.connect(this, "alignmentChanged(int)");
	inputMaskComboBox.activatedIndex.connect(this, "inputMaskChanged(int)");
	accessComboBox.activatedIndex.connect(this, "accessChanged(int)");

	QGridLayout echoLayout = new QGridLayout();
	echoLayout.addWidget(echoLabel, 0, 0);
	echoLayout.addWidget(echoComboBox, 0, 1);
	echoLayout.addWidget(echoLineEdit, 1, 0, 1, 2);
	echoGroup.setLayout(echoLayout);

	QGridLayout validatorLayout = new QGridLayout();
	validatorLayout.addWidget(validatorLabel, 0, 0);
	validatorLayout.addWidget(validatorComboBox, 0, 1);
	validatorLayout.addWidget(validatorLineEdit, 1, 0, 1, 2);
	validatorGroup.setLayout(validatorLayout);

	QGridLayout alignmentLayout = new QGridLayout();
	alignmentLayout.addWidget(alignmentLabel, 0, 0);
	alignmentLayout.addWidget(alignmentComboBox, 0, 1);
	alignmentLayout.addWidget(alignmentLineEdit, 1, 0, 1, 2);
	alignmentGroup. setLayout(alignmentLayout);

	QGridLayout inputMaskLayout = new QGridLayout();
	inputMaskLayout.addWidget(inputMaskLabel, 0, 0);
	inputMaskLayout.addWidget(inputMaskComboBox, 0, 1);
	inputMaskLayout.addWidget(inputMaskLineEdit, 1, 0, 1, 2);
	inputMaskGroup.setLayout(inputMaskLayout);

	QGridLayout accessLayout = new QGridLayout();
	accessLayout.addWidget(accessLabel, 0, 0);
	accessLayout.addWidget(accessComboBox, 0, 1);
	accessLayout.addWidget(accessLineEdit, 1, 0, 1, 2);
	accessGroup.setLayout(accessLayout);

	QGridLayout layout = new QGridLayout();
        layout.addWidget(echoGroup, 0, 0);
        layout.addWidget(validatorGroup, 1, 0);
        layout.addWidget(alignmentGroup, 2, 0);
        layout.addWidget(inputMaskGroup, 0, 1);
        layout.addWidget(accessGroup, 1, 1);
	setLayout(layout);

	setWindowTitle(tr("Line Edits"));
    }

    public void echoChanged(int index) {
	switch (index) {
	case 0:
	    echoLineEdit.setEchoMode(QLineEdit.Normal);
	    break;
	case 1:
	    echoLineEdit.setEchoMode(QLineEdit.Password);
	    break;
	case 2:
	    echoLineEdit.setEchoMode(QLineEdit.NoEcho);
	}
    }

    public void validatorChanged(int index)
    {
	switch (index) {
	case 0:
	    validatorLineEdit.setValidator(null);
	    break;
	case 1:
	    validatorLineEdit.setValidator(new QIntValidator(validatorLineEdit));
	    break;
	case 2:
	    validatorLineEdit.setValidator(new QDoubleValidator(-999.0,
								 999.0, 2, validatorLineEdit));
	}

	validatorLineEdit.setText("");
    }

    public void alignmentChanged(int index)
    {
	switch (index) {
	case 0:
	    alignmentLineEdit.setAlignment(Qt.AlignLeft);
	    break;
	case 1:
	    alignmentLineEdit.setAlignment(Qt.AlignCenter);
	    break;
	case 2:
	    alignmentLineEdit.setAlignment(Qt.AlignRight);
	}
    }

    public void inputMaskChanged(int index)
    {
	switch (index) {
	case 0:
	    inputMaskLineEdit.setInputMask("");
	    break;
	case 1:
	    inputMaskLineEdit.setInputMask("+99 99 99 99 99;_");
	    break;
	case 2:
	    inputMaskLineEdit.setInputMask("0000-00-00");
	    inputMaskLineEdit.setText("00000000");
	    inputMaskLineEdit.setCursorPosition(0);
	    break;
	case 3:
	    inputMaskLineEdit.setInputMask(">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#");
	}
    }

    public void accessChanged(int index)
    {
	switch (index) {
	case 0:
	    accessLineEdit.setReadOnly(false);
	    break;
	case 1:
	    accessLineEdit.setReadOnly(true);
	}
    }

    public static void main(String args[]) {
        QApplication.initialize(args);
	
        MainWindow lineedits = new MainWindow();
        lineedits.show();

        QApplication.exec();
    }
}
