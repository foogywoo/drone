#include "MetaGearEditor.h"

#include "MetaGear.h"
#include "SchemaEditor.h"
#include "GearListView.h"
#include "PlugPropertiesTable.h"

#include <qsplitter.h>
#include <qlayout.h>

MetaGearEditor::MetaGearEditor(QWidget *parent, MetaGear *metaGear, Engine *engine) :
  QWidget(parent),
  _metaGear(metaGear)
{  
  QBoxLayout *layout = new QVBoxLayout(this, 1);

  _schemaGui = new SchemaGui(_metaGear->getInternalSchema(), engine);

  _horizontalSplitter = new QSplitter(QSplitter::Horizontal, this);
  _verticalSplitter = new QSplitter(QSplitter::Vertical, _horizontalSplitter);

	_schemaEditor = new SchemaEditor(_horizontalSplitter, _schemaGui, engine);  
  
  _gearNavigatorView = new GearNavigatorView(_verticalSplitter,_schemaEditor);
  _gearNavigatorView->create();
  _plugPropertiesTable = new PlugPropertiesTable(_verticalSplitter);
  
  _horizontalSplitter->moveToFirst(_verticalSplitter);
  
  layout->addWidget(_horizontalSplitter);
  	
  QObject::connect(_schemaEditor, SIGNAL(gearSelected(GearGui*)), _plugPropertiesTable, SLOT(slotGearSelected(GearGui*)));
  
}

MetaGearEditor::~MetaGearEditor()
{
}

void MetaGearEditor::zoomInSchema()
{
	_schemaEditor->zoomIn();
}

void MetaGearEditor::zoomOutSchema()
{
	_schemaEditor->zoomOut();
}
