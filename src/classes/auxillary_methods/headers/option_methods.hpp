#ifndef PAINT_CALCULATION_OPTION_METHODS
#define PAINT_CALCULATION_OPTION_METHODS

#include "PaintDataContainer.hpp"
#include "AbstractDataContainer.hpp"

namespace common_option_methods {

	void clearValues(AbstractDataContainer *);
	void calculateResourceAmount(AbstractDataContainer const *);
	void loadPreset(AbstractDataContainer *);
	void writePaintParameters(AbstractDataContainer const *);

}

namespace paint_calculation_option_methods {

	void setPaintType(PaintDataContainer *);
	void setMaterialType(PaintDataContainer *);
	void setPaintConsumption(PaintDataContainer *);
	void setDivider(PaintDataContainer *);
	void setPercentage(PaintDataContainer *);
	void setSheetWidth(PaintDataContainer *);
	void setSheetLength(PaintDataContainer *);
	void setCirculation(PaintDataContainer *);
	void setPaintReserve(PaintDataContainer *);

}

namespace lacquer_calculation_option_methods {



}

#endif
