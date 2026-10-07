#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// ID de la estadistica de llaves en GameStatsManager.
// NO esta verificado oficialmente: si tras abrir el juego el Vault no muestra
// 5000 llaves, mira el log de Geode (linea "AutoBot: llaves antes/despues").
static constexpr const char* KEYS_STAT_ID = "21";
static constexpr int KEYS_AMOUNT = 5000;

class $modify(AutoBotMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		// MenuLayer::init se ejecuta cada vez que vuelves al menu: solo aplicar una vez por sesion.
		static bool applied = false;
		if (!applied) {
			applied = true;

			auto stats = GameStatsManager::sharedState();
			int before = stats->getStat(KEYS_STAT_ID);
			stats->setStat(KEYS_STAT_ID, KEYS_AMOUNT);

			// Las estadisticas se guardan junto con GameManager.
			GameManager::sharedState()->save();

			log::info("AutoBot: llaves antes = {}, despues = {}", before, stats->getStat(KEYS_STAT_ID));
		}

		return true;
	}
};
