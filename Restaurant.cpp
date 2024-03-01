#include "main.h"
 extern int MAXSIZE;
// extern int //COUNTDELETE;
class imp_res : public Restaurant
{
	public:	
		customer *cur;
		customer *waitList;
		customer *timeline;
		//customer *tableOrder;
		int numCus;
		int numWait;
		int numPeople;
		

		imp_res() {
			cur = nullptr;
			waitList = nullptr;
			timeline = nullptr;
			//tableOrder = nullptr;
			numCus = 0;
			numWait = 0;
			numPeople = 0;
		};

		~imp_res(){
			while (cur){
				removeCustomer(cur);
			}
			while (timeline){
				removeFromTimeLine(timeline);
			}
			while (waitList){
				removeCusFromWaitList(waitList);
			}
		}

		void swapCustomer(customer* p1, customer* p2){
			swap(p1->name, p2->name);
			swap(p1->energy, p2->energy);
		}

		customer* nodeAt(customer* head, int index){
			customer* trav = head;
			for (int i = 0; i < index; i++){
				trav = trav->next;
			}
			return trav;
		}

		void inssort2(customer* start, int n, int incr, int& N) {
			for (int i=incr; i<n; i+=incr){
				for (int j=i; j >= incr; j-=incr){
					customer* a1 = nodeAt(start, j);
					customer* a2 = nodeAt(start, j - incr);
					if (abs(a1->energy) >= abs(a2->energy)) {
						if (abs(a1->energy) > abs(a2->energy)){
							swapCustomer(a1, a2);
							N++;
						}
						else {
							customer* trav = timeline;
							while (trav->next) trav = trav->next;
							while (trav->name != a1->name && trav->name != a2->name){
								trav = trav->prev;
							}
							if (trav->name == a2->name){
								swapCustomer(a1, a2);
								N++;
							}
							else break;
						}
					}
					else break;
				}
			}
		}

		void shellsort(customer* list, int n, int& N) { // Shellsort
			for (int i=n/2; i>2; i/=2) // For each increment
				for (int j=0; j<i; j++) // Sort each sublist
					inssort2(nodeAt(list, j), n-j, i, N);
			inssort2(list, n, 1, N);
		}

		void addToKickList(customer*& kickList, customer* cus){
			kickList = new customer(cus->name, cus->energy, NULL, kickList);
			//COUNTDELETE++;
		}

		void clearKickList(customer*& kickList){
			while (kickList){
				customer* del = kickList;
				kickList = kickList->next;
				delete del;
				//COUNTDELETE--;
			}
		}

		bool isInTimeLine(customer* cus){
			customer* trav = timeline;
			while (trav){
				if (trav->name == cus->name) return 1;
				trav = trav->next;
			}
			return 0;
		}

		bool isInTable(string name){
			customer* trav = cur;
			for (int i = 0; i < numCus; i++){
				if (name == trav->name) return 1;
				trav = trav->next;
			}
			return 0;
		}

		void addToWaitList(customer* cus){							//add to the end of the queue
			if (!waitList){
				waitList = cus;
				numWait++;
				cus->next = NULL;
				cus->prev = NULL;
			}
			else {
				customer* add = waitList;
				while (add->next){
					add = add->next;
				}
				add->next = cus;
				cus->next = NULL;
				cus->prev = add;
				numWait++;
			}
		}

		customer* removeFromWaitList(){									//remove the first one in queue to manage position
			if (!waitList) return nullptr;
			customer* temp = waitList;
			waitList = waitList->next;
			if (waitList) waitList->prev = NULL;
			numWait--;
			return temp;
		}

		void removeCusFromWaitList(customer* cus){					//remove customer in the waitList from the restaurant
			if (cus == waitList){
				waitList = waitList->next;
				if (waitList) waitList->prev = NULL;
				delete cus;
			}
			else {
				customer* pPre = cus->prev;
				pPre->next = cus->next;
				if ((cus->next)) cus->next->prev = cus->prev;
				delete cus;
			}
			numWait--;
			//COUNTDELETE--;
		}

		void removeCustomer(customer* cus){							//remove customer from the table
			if (cus->next == cus && cus->prev == cus){
				delete cur;
				cur = nullptr;
				numCus--;
			}
			else {
				customer* prevCus = cus->prev;
				customer* nextCus = cus->next;
				int energyCus = cus->energy;
				prevCus->next = nextCus;
				nextCus->prev = prevCus;
				delete cus;
				numCus--;
				if (energyCus < 0) cur = prevCus;
				else cur = nextCus;
			}
			//COUNTDELETE--;
		}

		void addToTimeLine(customer* cus){							//add people to timeline
			if (!timeline){
				timeline = cus;
				numPeople++;
				cus->next = NULL;
				cus->prev = NULL;
			}
			else {
				customer* add = timeline;
				while (add->next){
					add = add->next;
				}
				add->next = cus;
				cus->next = NULL;
				cus->prev = add;
				numPeople++;
			}
		}

		void removeFromTimeLine(customer* cus){						//remove people from timeline
			if (cus == timeline){
				timeline = timeline->next;
				if (timeline) timeline->prev = NULL;
				delete cus;
			}
			else {
				customer* pPre = cus->prev;
				pPre->next = cus->next;
				if ((cus->next)) cus->next->prev = cus->prev;
				delete cus;
			}
			numPeople--;
			//COUNTDELETE--;
		}

		// void addToTableOrder(customer* cus){						//add to table order list
		// 	if (!tableOrder){
		// 		tableOrder = cus;
		// 		cus->next = NULL;
		// 	}
		// 	else {
		// 		customer* add = tableOrder;
		// 		while (add->next){
		// 			add = add->next;
		// 		}
		// 		add->next = cus;
		// 		cus->next = NULL;
		// 	}
		// }

		// void removeFromTableOrder(customer* cus){
		// 	if (cus == tableOrder){
		// 		tableOrder = tableOrder->next;
		// 		delete cus;
		// 	}
		// 	else {
		// 		customer* pPre = tableOrder;
		// 		while (pPre->next != cus){
		// 			pPre = pPre->next;
		// 		}
		// 		pPre->next = cus->next;
		// 		delete cus;
		// 	}
		// }

		void RED(string name, int energy)
		{
			//cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			//COUNTDELETE++;
			if ((!energy) || (numWait == MAXSIZE && numCus == MAXSIZE)){
				delete cus;
				//COUNTDELETE--;
				return;
			}
			if (!cur) {
				cur = cus;
				if (!isInTimeLine(cus)){
					customer *cusT = new customer(name, energy, nullptr, nullptr);
					addToTimeLine(cusT);
					//COUNTDELETE++;
				}
				// customer *cusO = new customer(name, energy, nullptr, nullptr);
				// addToTableOrder(cusO);
				cus->prev = cus;
				cus->next = cus;
				numCus++;
			}
			else {
				customer* temp = cur;
				for (int i = 0; i < numCus; i++){						//Check if there're some customer have the same name
					if (temp->name == name) {
						delete cus;
						//COUNTDELETE--;
						return;
					}
					temp = temp->next;
				}
				temp = waitList;
				while (temp){
					if (temp->name == name) {
						delete cus;
						//COUNTDELETE--;
						return;
					}
					temp = temp->next;
				}

				if (numCus == MAXSIZE && numWait < MAXSIZE) {
					addToWaitList(cus);			//if number of customers equal MAXSIZE
					customer *cusT = new customer(name, energy, nullptr, nullptr);
					//COUNTDELETE++;
					addToTimeLine(cusT);
					return;
				}
				if (numCus < MAXSIZE/2){						//add customer to the table when numCus < MAXSIZE/2
					if (energy >= cur->energy){					//add clockwisely
						if (cur->next == cur && cur->prev == cur){
							cus->next = cur->next;
							cus->prev = cur;
							cur->next = cus;
							cur->prev = cus;
						}
						else {
							customer* nextCur = cur->next;
							cus->prev = cur;
							cus->next = nextCur;
							nextCur->prev = cus;
							cur->next = cus;
						}
						cur = cus;
						numCus++;
					}
					else {								//add unclockwisely
						if (cur->prev == cur && cur->next == cur){
							cus->prev = cur->prev;
							cus->next = cur;
							cur->prev = cus;
							cur->next = cus;
						}
						else {
							customer* prevCur = cur->prev;
							cus->prev = prevCur;
							cus->next = cur;
							prevCur->next = cus;
							cur->prev = cus;
						}
						cur = cus;
						numCus++;
					}
				}
				else {										//add customer to the table when numCus >= MAXSIZE/2
					customer* p = cur;
					string nameAdd = "";
					int maxAbs = -9999999;
					int noAbs = -9999999;
					for (int i = 0; i < numCus; i++){			//find the one have biggest abs(RES)
						if (abs(energy - p->energy) > maxAbs){
							maxAbs = abs(energy - p->energy);
							noAbs = energy - p->energy;
							nameAdd = p->name;
						}
						p = p->next;
					}
					p = cur;
					for (int i = 0; i < numCus; i++){
						if (p->name == nameAdd) break;
						p = p->next;
					}
					if (noAbs < 0){
						customer* prevp = p->prev;
						cus->prev = prevp;
						cus->next = p;
						prevp->next = cus;
						p->prev = cus;
					}
					else {
						customer* nextp = p->next;
						cus->prev = p;
						cus->next = nextp;
						nextp->prev = cus;
						p->next = cus;
					}
					cur = cus;
					numCus++;
				}
				if (!isInTimeLine(cus)){
					customer *cusT = new customer(name, energy, nullptr, nullptr);
					addToTimeLine(cusT);
					//COUNTDELETE++;
				}
				// customer *cusO = new customer(name, energy, nullptr, nullptr);
				// addToTableOrder(cusO);
			}
		}

		// void BLUE(int num)									//BLUE xóa num người tableOrder
		// {
		// 	//cout << "blue "<< num << endl;
		// 	if (!numCus) return;
		// 	if (num > numCus) num = numCus;
		// 	for (int i = 1; i <= num; i++){						//kick num first customers
		// 		customer* pDel = tableOrder;
		// 		customer* rem = cur;
		// 		for (int k = 0; k < numCus; k++){
		// 			if (rem->name == pDel->name) break;
		// 			rem = rem->next;
		// 		}
		// 		customer* pDelT = timeline;
		// 		while (pDelT->name != rem->name){
		// 			pDelT = pDelT->next;
		// 		}
		// 		removeFromTimeLine(pDelT);
		// 		removeCustomer(rem);
		// 		removeFromTableOrder(pDel);
		// 	}
		// 	if (!waitList) return;
		// 	else {
		// 		while (waitList && numCus < MAXSIZE){
		// 			customer* cus = removeFromWaitList();
		// 			RED(cus->name, cus->energy);
		// 			delete cus;
		// 		}
		// 	}
		// }

		void BLUE(int num)										//BLUE xóa num người timeline
		{
			//cout << "blue "<< num << endl;
			if (!numCus) return;
			if (num > numCus) num = numCus;
			
			for (int i = 1; i <= num; i++){						//kick num first customers
				//customer* pDel = tableOrder;
				customer* pDelT = timeline;
				while (!isInTable(pDelT->name)){
					pDelT = pDelT->next;
				}
				customer* rem = cur;
				for (int k = 0; k < numCus; k++){
					if (rem->name == pDelT->name) break;
					rem = rem->next;
				}
				// while (pDel){
				// 	if (pDel->name == pDelT->name) break;
				// 	pDel = pDel->next;
				// }
				
				removeFromTimeLine(pDelT);
				removeCustomer(rem);
				//removeFromTableOrder(pDel);
			}

			if (!waitList) return;
			else {
				while (waitList && numCus < MAXSIZE){
					customer* cus = removeFromWaitList();
					RED(cus->name, cus->energy);
					delete cus;
					//COUNTDELETE--;
				}
			}
		}

		void PURPLE()
		{
			//cout << "purple"<< endl;
			if (numWait <= 1) return;
			int N = 0;
			int maxAbsEner = -9999999;
			customer* trav = waitList;
			while (trav){
				if (abs(trav->energy) > maxAbsEner) maxAbsEner = abs(trav->energy);
				trav = trav->next;
			}
			trav = waitList;
			while (trav->next) trav = trav->next;
			int count = 0;
			while (abs(trav->energy) != maxAbsEner){				//Find start node
				trav = trav->prev;
				count++;
			}
			
			shellsort(waitList, numWait - count, N);
			//cout << "NumSwap: " << N << " ";
			BLUE(N%MAXSIZE);
		}

		void REVERSAL()
		{
			//cout << "reversal" << endl;
			if (numCus <= 1) return;
			customer* trav = cur;
			customer* tempCur = cur;
			int pos = 0;
			for (int i = 0; i < numCus; i++){
				if (trav->energy > 0) pos++;
				trav = trav->next;
			}
			trav = cur;				
			for (int i = 0; i < numCus; i++){						//find first pos num unclockwisely
				if (trav->energy < 0) trav = trav->prev;
				else break;
			}
			customer* trav2 = cur->next; 
			for (int i = 0; i < numCus; i++){						//find last pos num clockwwisely
				if (trav2->energy < 0) trav2 = trav2->next;
				else break;
			}
			for (int i = 0; i < pos/2; i++){
				if (trav == cur) cur = trav2;
				swap(trav->energy, trav2->energy);					//swap
				swap(trav->name, trav2->name);
				trav = trav->prev;
				for (int j = 0; j < numCus; j++){					//find next pos num unclockwisely
					if (trav->energy * trav2->energy < 0) trav = trav->prev;
					else break;
				}
				trav2 = trav2->next;
				for (int j = 0; j < numCus; j++){					//find next pos num clockwisely
					if (trav->energy * trav2->energy < 0) trav2 = trav2->next;
					else break;
				}
			}

			trav = tempCur;
			for (int i = 0; i < numCus; i++){						//find first neg num unclockwisely
				if (trav->energy > 0) trav = trav->prev;
				else break;
			}
			trav2 = tempCur->next; 
			for (int i = 0; i < numCus; i++){						//find fist neg num clockwwisely
				if (trav2->energy > 0) trav2 = trav2->next;
				else break;
			}
			for (int i = 0; i < (numCus - pos)/2; i++){
				if (trav == cur) cur = trav2;
				swap(trav->energy, trav2->energy);
				swap(trav->name, trav2->name);
				trav = trav->prev;
				for (int j = 0; j < numCus; j++){					//find next pos num unclockwisely
					if (trav->energy * trav2->energy < 0) trav = trav->prev;
					else break;
				}
				trav2 = trav2->next;
				for (int j = 0; j < numCus; j++){					//find next pos num clockwisely
					if (trav->energy * trav2->energy < 0) trav2 = trav2->next;
					else break;
				}
			}
		}

		void UNLIMITED_VOID()
		{
			//cout << "unlimited_void" << endl;
			if (numCus < 4) return;
			long long minSum = 9999999;
			//int maxWindow = 4;
			customer* leftMaxWin = cur;
			customer* rightMaxWin = cur;

			for (int i = 4; i <= numCus; i++){
				customer* left = cur;
				customer* right = cur;
				long long sum = 0;
				for (int j = 0; j < i; j++){
					sum += right->energy;
					right = right->next;
				}
				do{
					if (minSum >= sum){
						minSum = sum;
						//maxWindow = i;
						leftMaxWin = left;
						rightMaxWin = right->prev;
					}
					sum -= left->energy;
					sum += right->energy;
					right = right->next;
					left = left->next;
				}
				while (left != cur);
			}
			customer* trav = leftMaxWin;
			int minEn = 9999999;
			//print
			do {
				if (trav->energy < minEn) minEn = trav->energy;
				trav = trav->next;
			}
			while (trav != rightMaxWin->next);
			trav = leftMaxWin;
			while (trav->energy != minEn) trav = trav->next;
			customer* trav2 = trav;
			do {
				trav2->print();
				trav2 = trav2->next;
			}
			while (trav2 != rightMaxWin->next);
			trav2 = leftMaxWin;
			while (trav2 != trav){
				trav2->print();
				trav2 = trav2->next;
			}
		}

		void DOMAIN_EXPANSION()
		{
			//cout << "domain_expansion" << endl;
			if (numPeople <= 1) return;
			long long sumPos = 0;
			long long sumNeg = 0;
			customer* trav = cur;
			for (int i = 0; i < numCus; i++){
				if (trav->energy > 0) sumPos += trav->energy;
				else sumNeg += trav->energy;
				trav = trav->next;
			}
			trav = waitList;
			while (trav){
				if (trav->energy > 0) sumPos += trav->energy;
				else sumNeg += trav->energy;
				trav = trav->next;
			}

			// if (abs(sumPos) >= abs(sumNeg)){						//delete Negative Energy Customer
			// 	trav = cur;
			// 	int curNumCus = numCus;
			// 	for (int i = 0; i < curNumCus; i++){		//from table
			// 		if (trav->energy < 0){
			// 			customer* pDel = timeline;
			// 			// while (pDel->name != trav->name){
			// 			// 	pDel = pDel->next;
			// 			// }
			// 			// removeFromTimeLine(pDel);
			// 			pDel = tableOrder;
			// 			while (pDel->name != trav->name){
			// 				pDel = pDel->next;
			// 			}
			// 			removeFromTableOrder(pDel);

			// 			removeCustomer(trav);
			// 			trav = cur->next;						//negative -> cur = cur->prev
			// 		}
			// 		else trav = trav->next;
			// 	}
			// 	trav = waitList;
				
			// 	while (trav){							//from waitList
			// 		customer* pNext = trav->next;
			// 		if (trav->energy < 0) {
			// 			// customer* pDel = timeline;
			// 			// while (pDel->name != trav->name){
			// 			// 	pDel = pDel->next;
			// 			// }
			// 			// removeFromTimeLine(pDel);
						
			// 			removeCusFromWaitList(trav);
			// 			trav = pNext;
			// 		}
			// 		else trav = trav->next;
			// 	}
			// }
			// else {										//delete Positive Energy Customer
			// 	trav = cur;
			// 	int curNumCus = numCus;
			// 	for (int i = 0; i < curNumCus; i++){		//from table
			// 		if (trav->energy > 0){
			// 			customer* pDel = timeline;
			// 			// while (pDel->name != trav->name){
			// 			// 	pDel = pDel->next;
			// 			// }
			// 			// removeFromTimeLine(pDel);
			// 			pDel = tableOrder;
			// 			while (pDel->name != trav->name){
			// 				pDel = pDel->next;
			// 			}
			// 			removeFromTableOrder(pDel);

			// 			removeCustomer(trav);
			// 			trav = cur;
			// 		}
			// 		else trav = trav->next;
			// 	}
			// 	trav = waitList;
				
				
			// 	while (trav){							
			// 		customer* pNext = trav->next;	//from waitList
			// 		if (trav->energy > 0) {
						
			// 			// customer* pDel = timeline;
			// 			// while (pDel->name != trav->name){
			// 			// 	pDel = pDel->next;
			// 			// }
			// 			// removeFromTimeLine(pDel);

			// 			removeCusFromWaitList(trav);
			// 			trav = pNext;
			// 		}
			// 		else trav = trav->next;
			// 	}
			// }
			customer* kickList = NULL;
			if (abs(sumPos) >= abs(sumNeg)){		//Negative deleted		
				trav = timeline;
				//while (trav->next) trav = trav->next;

				while (trav){
					if (trav->energy < 0){				
						if (isInTable(trav->name)){								//Delete from table
							customer* travT = cur;
							for (int i = 0; i < numCus; i++){
								if (travT->name == trav->name) break;
								travT = travT->next;
							}
							// customer* pDel = tableOrder;
							// while (pDel->name != trav->name){
							// 	pDel = pDel->next;
							// }
							// removeFromTableOrder(pDel);
							removeCustomer(travT);
						}
						else {														//delete from waitList
							customer* travW = waitList;
							while (travW){
								if (travW->name == trav->name) break;
								travW = travW->next;
							}
							removeCusFromWaitList(travW);
						}	
						addToKickList(kickList, trav);
						customer* temp = trav;
						trav = trav->next;
						removeFromTimeLine(temp);
					}
					else trav = trav->next;
				}
			}
			else {
				trav = timeline;
				//while (trav->next) trav = trav->next;

				while (trav){
					if (trav->energy > 0){
						if (isInTable(trav->name)){								//Delete from table
							customer* travT = cur;
							for (int i = 0; i < numCus; i++){
								if (travT->name == trav->name) break;
								travT = travT->next;
							}
							// customer* pDel = tableOrder;
							// while (pDel->name != trav->name){
							// 	pDel = pDel->next;
							// }
							// removeFromTableOrder(pDel);
							removeCustomer(travT);
						}
						else {														//delete from waitList
							customer* travW = waitList;
							while (travW){
								if (travW->name == trav->name) break;
								travW = travW->next;
							}
							removeCusFromWaitList(travW);
						}
						addToKickList(kickList, trav);
						customer* temp = trav;
						trav = trav->next;
						removeFromTimeLine(temp);
					}
					else trav = trav->next;
				}
			}
			customer* travKL = kickList;
			while (travKL){
				travKL->print();
				travKL = travKL->next;
			}
			clearKickList(kickList);
			if (!waitList) return;
			else {
				while (waitList && numCus < MAXSIZE){
					customer* cus = removeFromWaitList();
					RED(cus->name, cus->energy);
					delete cus;
					//COUNTDELETE--;
				}
			}

		}

		void LIGHT(int num)
		{
			//cout << "light " << num << endl;
			if (!num){
				customer* pPrint = waitList;
				while (pPrint){
					pPrint->print();
					pPrint = pPrint->next;
				}
			}
			else if (num > 0){
				customer* pPrint = cur;
				for (int i = 0; i < numCus; i++){
					pPrint->print();
					pPrint = pPrint->next;
				}
			}
			else {
				customer* pPrint = cur;
				for (int i = 0; i < numCus; i++){
					pPrint->print();
					pPrint = pPrint->prev;
				}
			}
		}
};