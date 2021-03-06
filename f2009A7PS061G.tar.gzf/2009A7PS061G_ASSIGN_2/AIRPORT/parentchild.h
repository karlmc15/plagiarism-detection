//this file contains the process airport

	
void airport(struct allInfo **main_pointer, int noOfPassengers){
		printf("---------------------WELCOME TO AIRPORT-------------------\n");
		int i = 0;
		int pid = 0;
		int notentered = 0;
		int totpassengers = noOfPassengers;
		while(i<noOfPassengers){
				main_pointer[i]->isValid = entryCheck(main_pointer[i]);
				i++;
			}
			i = 0;
		while(i<noOfPassengers){
				if(main_pointer[i]->isValid > 240){
						main_pointer[i] = NULL;
						notentered++;
					}
					i++;
			}
			int j = 0;
			i = 0;
			while(i<noOfPassengers){
					if(main_pointer[i] == NULL){
							for(j = i+1;j<noOfPassengers;j++){
					//				printf("%s \n",main_pointer[i]->personal.firstName);
									main_pointer[j-1] = main_pointer[j];
								}
						}
						i++;
				}
				noOfPassengers = noOfPassengers - notentered;
				printf("Number of passengers entering airport %d\n",noOfPassengers);
				printf("------------CREATING CHILDREN------------\n");
		int array[5] = {0};
		for(i = 0; i< 5; i++){
				pid = fork();
				array[i] = pid;
				if(pid == 0){
						switch(i){
							case 4:baggageCounter(array, main_pointer, noOfPassengers);exit(0);
							case 2:securityCheck(array, main_pointer, noOfPassengers);exit(0);
							case 3:immigration(array, main_pointer, noOfPassengers);exit(0);
							case 1:waitingLounge(array, main_pointer, noOfPassengers);exit(0);
							case 0:boarding(array, main_pointer, noOfPassengers);exit(0);
							}
					}
			}
			sleep(1);
			printf("---------------------ALL CHILDREN CREATED-------------------\n");
			printf("------------------STARTING BOARDING PROCEDURE------------------\n");
			i = 0;
			kill(array[4], SIGCONT);
			kill(getpid(), SIGSTOP);
			//parent gets call to start boarding
			kill(array[0], SIGCONT);
			kill(getpid(), SIGSTOP);
			//parent gets signal from boarding
			printf("Waiting lounge and children asked to exit \n");
			sleep(2);
			kill(array[1], SIGCONT);
			kill(getpid(), SIGSTOP);
			int boarded = 0;
			i = 0;
			while(i<noOfPassengers){
					if(passengerCheck(main_pointer[i])==1){
							boarded++;
						}
						i++;
				}
				printf("No of passengers entered %d, no of passengers boarded %d \n",totpassengers, boarded);
				printf("------------------------TELLING ALL CHILDREN TO EXIT----------------------------\n");
				sleep(1);
				kill(array[4], SIGCONT);
				kill(array[3], SIGCONT);
				kill(array[2], SIGCONT);
				kill(array[1], SIGCONT);
				kill(array[0], SIGCONT);
			while(wait(NULL)!=-1);
			printf("--------------------------ALL CHILDREN HAVE EXITED---------------------------------- \n");
			printf("----------------------------AIRPORT SHUTTING DOWN-----------------------------\n");
			exit(0);
	}

