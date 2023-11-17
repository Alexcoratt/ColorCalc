#ifndef PAINT_CALCULATION_OPTION_METHODS
#define PAINT_CALCULATION_OPTION_METHODS

#include "PaintDataDispatcher.hpp"
#include "LacquerDataDispatcher.hpp"
#include "FoilDataDispatcher.hpp"

namespace common_option_methods {

	void clearValues(AbstractDataDispatcher *);
	void calculateResourceAmount(AbstractDataDispatcher const *);
	void writeParameters(AbstractDataDispatcher const *);

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

	void createPaintPreset(PaintDataDispatcher *);
	void updatePaintPreset(PaintDataDispatcher *);
	void removePaintPreset(PaintDataDispatcher *);

}

namespace lacquer_calculation_option_methods {

	void setPercentage(LacquerDataDispatcher *);
	void setConsumption(LacquerDataDispatcher *);
	void setSheetLength(LacquerDataDispatcher *);
	void setSheetWidth(LacquerDataDispatcher *);
	void setCircualtion(LacquerDataDispatcher *);
	void loadLacquerPreset(LacquerDataDispatcher *);

	void createLacquerPreset(LacquerDataDispatcher *);
	void updateLacquerPreset(LacquerDataDispatcher *);
	void removeLacquerPreset(LacquerDataDispatcher *);

}

namespace foil_calculation_option_methods {

	void setCirulation(FoilDataDispatcher *);
	void setLength(FoilDataDispatcher *);
	void setSheetNumber(FoilDataDispatcher *);

	void createFoilPreset(FoilDataDispatcher *);
	void updateFoilPreset(FoilDataDispatcher *);
	void removeFoilPreset(FoilDataDispatcher *);

}

#endif
