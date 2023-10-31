#ifndef PAINT_CALCULATION_OPTION_METHODS
#define PAINT_CALCULATION_OPTION_METHODS

#include "PaintDataContainer.hpp"
#include "LacquerDataContainer.hpp"

namespace common_option_methods {

	void clearValues(AbstractDataContainer *);
	void calculateResourceAmount(AbstractDataContainer const *);
	void loadPreset(AbstractDataContainer *);
	void writePaintParameters(AbstractDataContainer const *);

}

namespace paint_calculation_option_methods {

	void setPaintType(PaintDataContainer *);
	void setMaterialType(PaintDataContainer *);
	void setConsumption(PaintDataContainer *);
	void setDivider(PaintDataContainer *);
	void setPercentage(PaintDataContainer *);
	void setSheetWidth(PaintDataContainer *);
	void setSheetLength(PaintDataContainer *);
	void setCirculation(PaintDataContainer *);
	void setReserve(PaintDataContainer *);

}

namespace lacquer_calculation_option_methods {

	void setPercentage(LacquerDataContainer *);
	void setConsumption(LacquerDataContainer *);
	void setSheetLength(LacquerDataContainer *);
	void setSheetWidth(LacquerDataContainer *);
	void setCircualtion(LacquerDataContainer *);

}

#endif
