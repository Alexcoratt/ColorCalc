#ifndef PAINT_CALCULATION_OPTION_METHODS
#define PAINT_CALCULATION_OPTION_METHODS

#include "PaintDataContainer.hpp"

namespace paint_calculation_option_methods {

	void writePaintParameters(PaintDataContainer const *);
	void setPaintType(PaintDataContainer *);
	void setMaterialType(PaintDataContainer *);
	void setPaintConsumption(PaintDataContainer *);
	void setDivider(PaintDataContainer *);
	void setPercentage(PaintDataContainer *);
	void setSheetWidth(PaintDataContainer *);
	void setSheetLength(PaintDataContainer *);
	void setCirculation(PaintDataContainer *);
	void setPaintReserve(PaintDataContainer *);
	void loadPreset(PaintDataContainer *);
	void clearValues(PaintDataContainer *);
	void calculatePaintAmount(PaintDataContainer const *);

}

#endif
