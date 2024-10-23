// Name: Hanbi Gong
// Seneca Student ID: 111932224
// Seneca email: hgong12@myseneca.ca
// Date of completion: Aug 2nd, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"
#include "Utilities.h"
#include <fstream>

namespace seneca {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
        // Load the contents of the file and populate m_activeLine
        std::ifstream inputFile(file);
        if (!inputFile) {
            std::cerr << "Error opening file: " << file << std::endl;
        }

        std::string str, ws, nextWs;
        std::vector<std::pair<std::string, std::string>> links;

        // workstation -> nextWorkstation ¦�� ����
        while (std::getline(inputFile, str)) {
            // Parse each record (WORKSTATION|NEXT_WORKSTATION)
            Utilities util; // might need to set delimeter as | 
            size_t next_pos = 0;
            bool more = true;
            
            ws = util.extractToken(str, next_pos, more);
            nextWs = util.extractToken(str, next_pos, more);
            links.emplace_back(ws, nextWs);
        }
        inputFile.close();

        std::for_each(links.begin(), links.end(), [&stations, this](const std::pair<std::string, std::string>& link) {
            auto it = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws){
                return ws->getItemName() == link.first;
                });
            auto nextIt = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                return ws->getItemName() == link.second;
                });
            // station, station�� �����Ѵ�.
            if (it != stations.end()) {
                m_activeLine.push_back(*it);
                if (nextIt != stations.end()) {
                    (*it)->setNextStation(*nextIt);
                }
            }
         });
        
        auto firstIt = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
            return std::none_of(links.begin(), links.end(), [&](const std::pair<std::string, std::string>& link) {
                return link.second == ws->getItemName();
                });
            });

        if (firstIt != m_activeLine.end()) {
            m_firstStation = *firstIt;
        }
        else {
            throw std::runtime_error("Failed to identify the first station in the assembly line.");
        }

        m_cntCustomerOrder = g_pending.size();
	}
	void LineManager::reorderStations()
	{
        std::vector<Workstation*> reordered;
        Workstation* current = m_firstStation;
        while (current) {
            reordered.push_back(current);
            current = current->getNextStation();
        }
        m_activeLine = reordered;
	}

	bool LineManager::run(std::ostream& os)
	{
        static size_t iteration = 0;
        os << "Line Manager Iteration: " << ++iteration << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
            ws->fill(os);
            });
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* ws) {
            ws->attemptToMoveOrder();
            });
        return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());

	}

	void LineManager::display(std::ostream& os) const
	{
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
            ws->display(os);
          });
	}
}