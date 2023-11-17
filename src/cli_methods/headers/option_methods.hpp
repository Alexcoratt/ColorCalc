#ifndef PAINT_CALCULATION_OPTION_METHODS
#define PAINT_CALCULATION_OPTION_METHODS

#include "PaintDataDispatcher.hpp"
#include "LacquerDataDispatcher.hpp"
#include "FoilDataDispatcher.hpp"

namespace common_option_methods {

	void clearValues(AbstractDataDispatcher *);
	void calculateResourceAmount(AbstractDataDispatcher const *);
	void writeParameters(AbstractDataDispatcher const *);

	void createPreset(AbstractDataDispatcher *);
	void updatePreset(AbstractDataDispatcher *);
	void removePreset(AbstractDataDispatcher *);

}

namespace paint_calculation_option_methods {

	void setPaintType(PaintDataDispatcher *);
	void setMaterialType(PaintDataDispatcher *);
	void setConsumption(PaintDataDispatcher *);
	void setDivider(PaintDataDispatcher *);
	void setPercentage(PaintDataDispatcher *);
	void setSheetWidth(PaintDataDispatcher *);
	void setSheetLength(PaintDataDispatcher *);
	void setCirculation(PaintDataDispatcher *);
	void setReserve(PaintDataDispatcher *);
	void loadPaintPreset(PaintDataDispatcher *);

}

namespace lacquer_calculation_option_methods {

	void setPercentage(LacquerDataDispatcher *);
	void setConsumption(LacquerDataDispatcher *);
	void setSheetLength(LacquerDataDispatcher *);
	void setSheetWidth(LacquerDataDispatcher *);
	void setCircualtion(LacquerDataDispatcher *);
	void loadLacquerPreset(LacquerDataDispatcher *);

}

namespace foil_calculation_option_methods {

	void setCirulation(FoilDataDispatcher *);
	void setLength(FoilDataDispatcher *);
	void setSheetNumber(FoilDataDispatcher *);
	void setWidthReserve(FoilDataDispatcher *);
	void loadFoilPreset(FoilDataDispatcher *);
	void calculateFoilRollerLength(FoilDataDispatcher const *);

}

#endif
