#ifndef PAINT_CALCULATION_OPTION_METHODS
#define PAINT_CALCULATION_OPTION_METHODS

#include "PaintDataDispatcher.hpp"
#include "LacquerDataDispatcher.hpp"
#include "FoilDataDispatcher.hpp"
#include "FoilRollsDataDispatcher.hpp"

namespace common_option_methods {

	void clearValues(IDataManager *);
	void calculateResourceAmount(IDataManager const *);
	void writeParameters(IDataManager const *);

	void loadPreset(IDataManager *);
	void createPreset(IDataManager *);
	void updatePreset(IDataManager *);
	void removePreset(IDataManager *);

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

}

namespace lacquer_calculation_option_methods {

	void setPercentage(LacquerDataDispatcher *);
	void setConsumption(LacquerDataDispatcher *);
	void setSheetLength(LacquerDataDispatcher *);
	void setSheetWidth(LacquerDataDispatcher *);
	void setCircualtion(LacquerDataDispatcher *);

}

namespace foil_calculation_option_methods {

	void setCirulation(FoilDataDispatcher *);
	void setLength(FoilDataDispatcher *);
	void setWidth(FoilDataDispatcher *);
	void setSheetNumber(FoilDataDispatcher *);
	void setLengthReserve(FoilDataDispatcher *);
	void setWidthReserve(FoilDataDispatcher *);
	void calculateFoilRollLength(FoilDataDispatcher const *);
	void writeSuitableRolls(FoilDataDispatcher const *);

}

namespace foil_rolls_option_methods {

	void setLength(FoilRollsDataDispatcher *);
	void setWidth(FoilRollsDataDispatcher *);

}

#endif
