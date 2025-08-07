public OnDialogResponse(playerid, dialogid, response, listitem, inputtext())
(
	if(dialogid != D_LOGIN && !Logged(playerid) && !PlayerCache(playerid)(pLauncherLogged))
	(
		SendClientMessage(playerid, COLOR_GREEN, Nie hackuj bo potem ja musze siedzieć przy kodzie zamiast na plaży...  :/) 
		Kick(playerid)
		return 1
	)
	
	if(dialogid != D_LOGIN && dialogid != D_INFO)
	(
		hrp_DialogLog((DIALOG) Gracz %s (uid: %d) odpalil dialog o id %d | Response: %s | Listitem: %s | inputtext: %s, PlayerName(playerid), PlayerCache(playerid)(pUID), dialogid, response, listitem, inputtext)
	)
	
	if(PlayerCache(playerid)(pDialog) != dialogid)
	(
		if(dialogid == D_LOGIN)
		(
			hrp_DialogLog((DIALOG WARNING) Gracz %s (uid: %d) | Prawidlowy dialog: %d | Aktualny dialog: %d | Response: %s | Listitem: %s | inputtext: %s, PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pDialog), dialogid, response, listitem, *****)
			SendClientMessage(playerid, COLOR_GREEN, Nie hackuj bo potem ja musze siedzieć przy kodzie zamiast na plaży...  :/)
			Kick(playerid)
			return 1
		)
		if(dialogid != D_LOGIN && Logged(playerid))
		(
			hrp_DialogLog((DIALOG WARNING) Gracz %s (uid: %d) | Prawidlowy dialog: %d | Aktualny dialog: %d | Response: %s | Listitem: %s | inputtext: %s, PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pDialog), dialogid, response, listitem, inputtext)
		)
	)
	
	// printf(OnDialogResponse(%d, %d, %d, listitem, inputtext()), playerid, dialogid, response)
    if (strfind(inputtext, %) != -1)
    (
        printf((hack) Gracz %s (UID: %d, GID: %d) to niezly cwaniaczek. Probowal nam scrashowac serwer przez dialogi., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))
        return 1
    )
	// printf(OnDialogResponse(%d, %d, %d, listitem, inputtext()) clean, playerid, dialogid, response)

	if(dialogid == D_INFO)
	(
		return 1
	)
	if(dialogid == D_LOGIN)
	(
		if(response)
		(
			password(64), data(128), done = false
			if(strlen(inputtext) )= 24 || strlen(inputtext) (= 0)
			(
				PlayerCache(playerid)(pLogTries) --
				ShowPlayerDialog(playerid, D_LOGIN, DIALOG_STYLE_PASSWORD, Panel logowania, Witaj na serwerze SERVER_NAME.\nWprowadź hasło do konta, aby móc rozpocząć grę.\n\n(FF0000)* Podane hasło jest nieprawidłowe, spróbuj ponownie, Zaloguj, Wyjdź)

				AddPlayerLoginLog(playerid, false)
				return 1
			)
			mysql_real_escape_string(inputtext, password)
			mysql_query_format(SELECT user_login, user_admin, user_premium, user_premium_time, user_gamepoints, user_color FROM live_users WHERE user_pass = MD5(%s) AND user_id = %d LIMIT 1, password, PlayerCache(playerid)(pGID))
			
   			print((log) Proces logowania rozpoczęty...)

			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				printf((log) Logowanie gracza %s (UID: %d, GID: %d) przebiegło pomyślnie., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))

				sscanf(data, p(|)s(64)ddddd, PlayerCache(playerid)(pGlobalName), PlayerCache(playerid)(pAdmin), PlayerCache(playerid)(pPremium), PlayerCache(playerid)(pPremiumTime), PlayerCache(playerid)(pGamePoints), PlayerCache(playerid)(pUserColor))
				AddPlayerLoginLog(playerid, true)
				
				done = true
			)
	   		else
			(
				if(PlayerCache(playerid)(pLogTries))
				(
					printf((log) Wprowadzono błędne hasło dla gracza %s (UID: %d, GID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))

					PlayerCache(playerid)(pLogTries) --
					ShowPlayerDialog(playerid, D_LOGIN, DIALOG_STYLE_PASSWORD, Panel logowania, Witaj na serwerze SERVER_NAME.\nWprowadź hasło do konta, aby móc rozpocząć grę.\n\n(FF0000)* Podane hasło jest nieprawidłowe, spróbuj ponownie, Zaloguj, Wyjdź)

					AddPlayerLoginLog(playerid, false)
				)
				else
				(
					printf((log) Gracz %s (UID: %d, GID: %d) przekroczył limit prób logowania, zostaje wyrzucony z serwera., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))

					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Przekroczyłeś limit wykonywania prób logowania.\nZostajesz wyrzucony z serwera., Zamknij, )
					Kick(playerid)
				)
				done = false
			)
			mysql_free_result()
			
			if(done)	(
				Logged(playerid) = true
				OnPlayerLogin(playerid)
			)
			return 1
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Opuszczasz grę - zapraszamy ponownie.\n\n\t\t\tEkipa SERVER_NAME., Zamknij, )
			Kick(playerid)
			return 1
		)
	)
	if(dialogid == D_LIST_PLAYER_CARS)
	(
		if(response)
		(
			string(128), vehuid, veh_name(32)
			sscanf(inputtext, ds(32), vehuid, veh_name)
			
			vehid = GetVehicleID(vehuid)
			if(vehid == INVALID_VEHICLE_ID)
			(
				// Dodajemy komisy
				
				mysql_query_format(SELECT * FROM hrp_cars WHERE car_uid = %d AND car_timeleft ) %d, vehuid, gettime())
				mysql_store_result()
				if(mysql_num_rows() ) 0)
				(
					GuiMsg(playerid, Ten pojazd nie dotarł jeszcze do miasta., 1)
					mysql_free_result()
					return 1
				)
				else
				(
					mysql_free_result()
				)
				
				/*
				if(PlayerCache(playerid)(pCarSpawned) ) 0)
				(
					bool:house = false
					
					foreach(Doors, d)
					(
						if(DoorData(d)(dUID))
						(
							if(DoorData(d)(dOwnerType) == OWNER_PLAYER && DoorData(d)(dOwner) == PlayerCache(playerid)(pUID))
							(
								house = true
							)
						)
					)
					
					if(!house)
					(
						d = GetDoorID(PlayerCache(playerid)(pHouse))
						if(d != -1)
						(
							if(DoorData(d)(dUID))
							(
								house = true
							)
						)
					)
					
					if(!house)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz zespawnować wiecej pojazdów nie mając domu., OK, )
						return 1
					)
				)
				*/
			
				if(!PlayerCache(playerid)(pPremium))
				(
					if(PlayerCache(playerid)(pCarSpawned) )= STANDARD_VEHICLES)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz zespawnować wiecej pojazdów niż 1.\nOdspawnuj jakiś pojazd.\n\nOsoby posiadające konto premium mogą zespawnować ich 3., OK, )
						return 1
					)
				)
				else
				(
					if(PlayerCache(playerid)(pCarSpawned) )= PREMIUM_VEHICLES)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz zespawnować wiecej pojazdów niż 3.\nOdspawnuj jakiś pojazd., OK, )
						return 1
					)
				)
				
				SpawnVehicle(vehuid)
				PlayerCache(playerid)(pCarSpawned) ++
				
				format(string, sizeof(string), Pojazd %s (UID: %d) został zespawnowany pomyślnie., veh_name, vehuid)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
			)
			else
			(
				UnspawnVehicle(vehuid)
				PlayerCache(playerid)(pCarSpawned) --

				format(string, sizeof(string), Pojazd %s (UID: %d) został odspawnowany pomyślnie., veh_name, vehuid)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_LIST_SPAWNED_CARS)
	(
		if(response)
		(
   			vehid = strval(inputtext), Float:x, Float:y, Float:z, string(128)
   			GetVehiclePos(vehid, x, y, z)
		  		
   			SetPlayerCheckpoint(playerid, x, y, z, 5.0)
			Checkpoint(playerid) = 1
		   		
   			format(string, sizeof(string), Namierzony został pojazd \%s\ (SampID: %d, UID: %d).\nAby anulować namierzanie, wpisz komendę /v namierz., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CHANGE_PICKUP)
	(
		if(response)
		(
	 		doorid = ChangePickup(playerid), string(128)
			DoorData(doorid)(dPickupID) = PickupIDs(listitem)
			SaveDoor(doorid, SAVE_DOOR_THINGS)
			
			DestroyPickup(doorid)
			CreatePickup(DoorData(doorid)(dPickupID), 2, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), DoorData(doorid)(dEnterVW))

			format(string, sizeof(string), Model pickupa dla drzwi %s (SampID: %d, UID: %d) został pomyślnie zmieniony., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Model pickupa drzwi został pomyślnie zmieniony., OK, )
			
			ChangePickup(playerid) = -1
			
			ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil model pickupa w drzwiach %s (SampID: %d, UID: %d). Nowy model: %d., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), DoorData(doorid)(dPickupID))
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_INTERIOR)
	(
		if(response)
		(
			string(32)
			
			format(string, sizeof(string), interior %d, strval(inputtext))
			cmd_adrzwi(playerid, string)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DOOR_OPTIONS)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					ShowPlayerDialog(playerid, D_CHANGE_DOOR_NAME, DIALOG_STYLE_INPUT, Opcje drzwi » Zmień nazwę, Wprowadź nową nazwę dla tych drzwi.\nOwa nazwa będzie wyświetlana po wejściu w pickup przed budynkiem.\n\nPoniżej wypisane są znaczniki, zmieniające kolor tekstu:\n\n(r) - czerwony\n(g) - zielony\n(p) - różowy\n(b) - niebieski\n(w) - biały\n(h) - rozjaśnia kolor, Zmień, Anuluj)
				)
				case 1:
				(
					ShowPlayerDialog(playerid, D_CHANGE_ENTER_PRICE, DIALOG_STYLE_INPUT, Opcje drzwi » Koszt wstępu, Wprowadź koszt wstępu do budynku.\nPieniądze będą przelewane bezpośrednio na konto właściciela budynku., Zmień, Anuluj)
				)
				case 2:
				(
					list_groups(256), group_id_fix
					format(list_groups, sizeof(list_groups), (C0C0C0)Slot\tNazwa oraz UID grupy(FFFFFF))

					for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
					(
			  			if(PlayerGroup(playerid)(slot)(gUID))
						(
				  			group_id_fix = PlayerGroup(playerid)(slot)(gID)
							format(list_groups, sizeof(list_groups), %s\n%d\t%s (%d), list_groups, slot + 1, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			 			)
					)
					ShowPlayerDialog(playerid, D_ASSIGN_DOOR, DIALOG_STYLE_LIST, Opcje drzwi » Przypisz pod grupę, list_groups, Wybierz, Anuluj)
				)
				case 3:
				(
					doorid = GetPlayerDoorID(playerid)
					if(doorid == INVALID_DOOR_ID)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w budynku., OK, )
						return 1
					)
					if(!strlen(DoorData(doorid)(dAudioURL)))
					(
						ShowPlayerDialog(playerid, D_CHANGE_DOOR_AUDIO, DIALOG_STYLE_INPUT, Opcje drzwi » Muzyka spoza gry, Wprowadź link do muzyki lub radia, które usłyszą wszyscy przebywający w tym budynku.\nLink nie może przekroczyć 128 znaków.\n\nUpewnij się, że link jest poprawny w innym wypadku muzyka może nie być słyszalna., Graj, Anuluj)
					)
					else
					(
						// Wyłącz muze wszystkim, którzy są w pomieszczeniu
						foreach(Player, i)
						(
							if(Logged(i) && Spawned(i))
							(
								if(GetPlayerDoorID(i) == doorid)
								(
									if(PlayerCache(i)(pAudioHandle))
									(
										//Audio_Stop(i, PlayerCache(i)(pAudioHandle))
										PlayerCache(i)(pAudioHandle) = 0
										StopAudioStreamForPlayer(i)
									)
								)
							)
						)
						
						strmid(DoorData(doorid)(dAudioURL), , 0, 0)
						SaveDoor(doorid, SAVE_DOOR_AUDIO)
						
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Muzyka spoza gry dla tego budynku została wyłączona.\nAby włączyć muzykę spoza gry, wybierz tę opcję ponownie., OK, )
					)
				)
				case 4:
				(
					doorid = GetPlayerDoorID(playerid)
					if(doorid == INVALID_DOOR_ID)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w budynku., OK, )
						return 1
					)
					
 		  			// Usuń stare obiekty z tego VW (jeśli są)
					for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
					(
						if(IsValidDynamicObject(object_id))
						(
							if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID, DoorData(doorid)(dUID)))
							(
								DestroyDynamicObject(object_id)
					  		)
						)
					)
					
					hrp_SetPlayerPos(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ))

					SetPlayerInterior(playerid, DoorData(doorid)(dEnterInt))
					SetPlayerVirtualWorld(playerid, DoorData(doorid)(dEnterVW))
					
					hrp_TogglePlayerControllable(playerid, true)
					PlayerCache(playerid)(pDoorFreeze) = 3
					
   					object_id, object_uid, object_model,
						Float:object_posx, Float:object_posy, Float:object_posz,
						Float:object_rotx, Float:object_roty, Float:object_rotz,
						object_world, object_interior, Float:object_distance

					data(128), string(128)
					mysql_query_format(SELECT * FROM hrp_objects WHERE object_world = %d, DoorData(doorid)(dUID))

					mysql_store_result()
					if(mysql_num_rows() != 0)
					(
						while(mysql_fetch_row(data, |))
						(
							sscanf(data, p(|)ddffffffddf, object_uid, object_model, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_world, object_interior, object_distance)
							object_id = CreateDynamicObject(object_model, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_world, object_interior, -1, object_distance)

							Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, object_uid)
						)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Obiekty dla tych drzwi nie zostały wgrane., OK, )
					)
					mysql_free_result()
					
					// załąduj materiały
					for(objectid = 0  objectid ( MAX_OBJECTS objectid++)
					(
						if(IsValidDynamicObject(objectid))
						(
							if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, DoorData(doorid)(dUID)))
							(
								LoadObjectMaterial(objectid)
								LoadObjectText(objectid)
							)
						)
					)
					
					LoadDoor(doorid, DoorData(doorid)(dUID))
					
					format(string, sizeof(string), Obiekty do drzwi %s (SampID: %d, UID: %d) zostały pomyślnie wczytane., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
				)
				case 5:
				(
   					LoadProductsList(playerid)
				)
				case 6:
				(
					doorid = GetPlayerDoorID(playerid)
					if(!DoorData(doorid)(dGarage))
					(
						DoorData(doorid)(dGarage) = true
						SaveDoor(doorid, SAVE_DOOR_THINGS)
						
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Opcje drzwi » Moliość przejazdu, Możliwość przejazdu samochodem przez drzwi została włączona.\n\nOd tej pory będziesz mógł wjechać dowolnym pojazdem do budynku.\nAby wjechać pojazdem do budynku skorzystaj z komendy /przejazd., OK, )
					)
					else
					(
						DoorData(doorid)(dGarage) = false
						SaveDoor(doorid, SAVE_DOOR_THINGS)
						
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Opcje drzwi » Moliość przejazdu, Możliwość przejazdu samochodem przez drzwi została wyłączona., OK, )
					)
				)
				case 7:
				(
					doorid = GetPlayerDoorID(playerid)
					if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Drzwi cywilne nie mają możliwości założenia dzwonka., OK, )
						return 1
					)
					if(!GroupTypeInfo(DoorData(doorid)(dOwner))(gBell))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Grupa, która jest właścicielem tych drzwi nie może posiadać dzwonka., OK, )
						return 1
					)
					if(DoorData(doorid)(dBell))
					(
						DoorData(doorid)(dBell) = false
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Opcje drzwi » Dzwonek do drzwi, Dzwonek zostały wyłączony dla tych drzwi., OK, )
						return 1
					)
					else
					(
						DoorData(doorid)(dBell) = true
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Opcje drzwi » Dzwonek do drzwi, Dzwonek zostały włączony dla tych drzwi., OK, )
						return 1
					)
				)
				case 8:
				(
					ShowPlayerDialog(playerid,D_DOOR_SET_TIME,DIALOG_STYLE_INPUT,Opcje drzwi » Ustalanie godziny interioru,Wpisz poniżej godzinę, jaka ma panować wewnątrz interioru.,Gotowe,Anuluj)
				)
				case 9:
				(
					// usuwanie obiektów
					cap1 = random(sizeof(Captcha)),
					cap2 = random(sizeof(Captcha)),
					cap3 = random(sizeof(Captcha)),
					cap4 = random(sizeof(Captcha)),
					cap5 = random(sizeof(Captcha)),
					cap6 = random(sizeof(Captcha)),
					cap7 = random(sizeof(Captcha)),
					cap8 = random(sizeof(Captcha)),
					cap9 = random(sizeof(Captcha)),
					cap10 = random(sizeof(Captcha))
					
					dialMsg(256)
					format(PlayerCache(playerid)(pCaptcha), 16, %s%s%s%s%s%s%s%s%s%s, Captcha(cap1), Captcha(cap2), Captcha(cap3), Captcha(cap4), Captcha(cap5), Captcha(cap6), Captcha(cap7), Captcha(cap8), Captcha(cap9), Captcha(cap10))
					format(dialMsg, sizeof(dialMsg), Przepisz kod captcha, jeśli jesteś pewien, że chcesz usunąć obiekty w tych drzwiach.\n\nKod: (00AA00)%s, PlayerCache(playerid)(pCaptcha))
					
					ShowPlayerDialog(playerid, D_OBJECTS_DELETE, DIALOG_STYLE_INPUT, Usuwanie obiektów, dialMsg, Tak, Nie)
				)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CHANGE_DOOR_NAME)
	(
		if(response)
		(
			doorid = GetPlayerDoorID(playerid), string(256), door_name(32), esc_door_name(32)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w budynku, którym chcesz zmienić nazwę., OK, )
				return 1
			)
			if(strlen(inputtext) ) 32)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Podana nazwa jest za długa.\nNazwa drzwi nie została zmieniona., OK, )
				return 1
			)
	   		strmid(door_name, FormatTextDrawColors(inputtext), 0, strlen(inputtext))
			format(string, sizeof(string), Nazwa drzwi %s (SampID: %d, UID: %d) została zmieniona pomyślnie.\nNowa nazwa drzwi: %s., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), door_name)
			
			mysql_real_escape_string(door_name, esc_door_name)
			strmid(DoorData(doorid)(dName), esc_door_name, 0, strlen(esc_door_name), 32)
			SaveDoor(doorid, SAVE_DOOR_THINGS)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, Zamknij)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CHANGE_ENTER_PRICE)
	(
		if(response)
		(
			doorid = GetPlayerDoorID(playerid), price = strval(inputtext), string(128)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w budynku, którym chcesz zmienić koszt wstępu., OK, )
				return 1
			)
			if(strlen(inputtext) ) 6)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			if(price ( 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			DoorData(doorid)(dEnterPay) = price
			
			SaveDoor(doorid, SAVE_DOOR_THINGS)
			
			if(DoorData(doorid)(dEnterPay))
			(
				format(string, sizeof(string), Koszt wstępu do budynku został zmieniony.\nOpłata $%d będzie pobierana po wejściu do środka., DoorData(doorid)(dEnterPay))
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Opłata za wstęp do budynku została wyłączona., OK, )
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CHANGE_DOOR_AUDIO)
	(
		if(response)
		(
			doorid = GetPlayerDoorID(playerid), audio_url(128)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w budynku, którym chcesz włączyć audio., OK, )
				return 1
			)
			strmid(audio_url, inputtext, 0, strlen(inputtext), 128)
			
			if(strfind(audio_url, http://, true))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzony link nie jest poprawny.\nLink powinien rozpoczynać się od \http://\., OK, )
				return 1
			)
			if(strlen(audio_url) ) 128)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono za długi link do muzyki., OK, )
				return 1
			)
			
			urlEscaped(300)
            mysql_real_escape_string(inputtext, urlEscaped)
			strmid(DoorData(doorid)(dAudioURL), audio_url, 0, strlen(audio_url), 128)
			
			SaveDoor(doorid, SAVE_DOOR_AUDIO)

			// Załącz muze dla wszystkich, którzy są w pomieszczeniu
			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(GetPlayerDoorID(i) == doorid)
					(
						if(PlayerCache(i)(pAudioHandle))
						(
							//Audio_Stop(i, PlayerCache(i)(pAudioHandle))
							PlayerCache(i)(pAudioHandle) = 0
							StopAudioStreamForPlayer(i)
						)
			   	 		//PlayerCache(i)(pAudioHandle) = Audio_PlayStreamed(i, DoorData(doorid)(dAudioURL))
						PlayAudioStreamForPlayer(i, DoorData(doorid)(dAudioURL))
						PlayerCache(i)(pAudioHandle) = 1
					)
				)
			)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Link do audio został pomyślnie wprowadzony.\nMuzyka powinna być od teraz słyszalna - jeśli nie jest, oznacza to że link nie jest poprawny., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ASSIGN_DOOR)
	(
		if(response)
		(
			group_slot = strval(inputtext) - 1, doorid = GetPlayerDoorID(playerid), string(256)
			if(doorid == INVALID_DOOR_ID)
  			(
  				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w budynku, który chcesz przypisać., OK, )
   				return 1
			)
			if(group_slot ( 0)
			(
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Anulowano., 3000, 3)
				return 1
			)
			if(!IsPlayerPermissedGroup(playerid, PlayerGroup(playerid)(group_slot)(gUID), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień dla tej grupy., OK, )
				return 1
			)
			group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
			MainPlayerTable(playerid) = group_id_fix
			
			format(string, sizeof(string), Czy chcesz przypisać budynek %s (SampID: %d, UID: %d) pod grupę %s (UID: %d)?, DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			ShowPlayerDialog(playerid, D_ASSIGN_DOOR_ACCEPT, DIALOG_STYLE_MSGBOX, Opcje drzwi » Przypisz pod grupę, string, Tak, Nie)
			return 1
		)
		else
		(
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Anulowano., 3000, 3)
			return 1
		)
	)
	if(dialogid == D_ASSIGN_DOOR_ACCEPT)
	(
		if(response)
		(
			doorid = GetPlayerDoorID(playerid), string(128)
	  		if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w budynku, który chcesz przypisać., OK, )
				return 1
			)
			group_id_fix = MainPlayerTable(playerid)

			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
			(
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pHouse) == DoorData(doorid)(dUID))
						(
							PlayerCache(i)(pHouse) = 0
						)
					)
				)

				mysql_query_format(UPDATE hrp_characters SET char_house = 0 WHERE char_house = %d, DoorData(doorid)(dUID))
			)

			DoorData(doorid)(dOwnerType) = OWNER_GROUP
			DoorData(doorid)(dOwner) = GroupData(group_id_fix)(gUID)

			SaveDoor(doorid, SAVE_DOOR_THINGS)

			format(string, sizeof(string), Budynek %s (SampID: %d, UID: %d) został pomyślnie przypisany pod grupę.\nBudynek przypisano dla grupy %s (UID: %d)., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RAISE_ITEM)
	(
		if(response)
		(
			itemuid = strval(inputtext)
			OnPlayerRaiseItem(playerid, itemuid)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_OFFER)
	(
		customerid = GetOffererID(playerid)
		if(response)
		(
			if(Offer(customerid)(oPrice))
			(
				if(PlayerCache(playerid)(pBankNumber) && Offer(customerid)(oPayType) == PAYTYPE_NONE)
				(
					ShowPlayerDialog(playerid, D_OFFER_PAYTYPE, DIALOG_STYLE_MSGBOX, Oferta, Wybierz rodzaj płatności za daną ofertę., Gotówka, Karta)
				)
				else
				(
					Offer(customerid)(oPayType) = PAYTYPE_CASH
					OnPlayerAcceptOffer(playerid, customerid)
				)
			)
			else
			(
   				Offer(customerid)(oPayType) = PAYTYPE_CASH
				OnPlayerAcceptOffer(playerid, customerid)
			)
			return 1
		)
		else
		(
			OnPlayerRejectOffer(playerid, customerid)
			return 1
		)
	)
	if(dialogid == D_OFFER_PAYTYPE)
	(
		customerid = GetOffererID(playerid)
		if(response)
		(
			Offer(customerid)(oPayType) = PAYTYPE_CASH
			OnPlayerAcceptOffer(playerid, customerid)
			return 1
		)
		else
		(
			if(Offer(customerid)(oType) == OFFER_PAINT || 
				Offer(customerid)(oType) == OFFER_REPAIR || 
				Offer(customerid)(oType) == OFFER_REPAIR_ENGINE || 
				Offer(customerid)(oType) == OFFER_REPAIR_BODY || 
				Offer(customerid)(oType) == OFFER_REPAIR_FLUIDS || 
				Offer(customerid)(oType) == OFFER_REPAIR_FILTER || 
				Offer(customerid)(oType) == OFFER_REPAIR_COOLER || 
				Offer(customerid)(oType) == OFFER_MANDATE || 
				Offer(customerid)(oType) == OFFER_PRODUCT ||
				Offer(customerid)(oType) == OFFER_MONTAGE ||
				Offer(customerid)(oType) == OFFER_REFUEL)
			(
				if(PlayerCache(playerid)(pBusinessCard) ) 0)
				(
					Offer(customerid)(oPayType) = PAYTYPE_BCARD
				)
				else
				(
					Offer(customerid)(oPayType) = PAYTYPE_CARD	
				)
			)
			else
			(
				Offer(customerid)(oPayType) = PAYTYPE_CARD	
			)
			OnPlayerAcceptOffer(playerid, customerid)
			return 1
		)
	)
	if(dialogid == D_OFFER_LIST)
	(
		if(response)
		(
			offer_name(24)
			sscanf(inputtext, »s(24), offer_name)
			
			cmd_oferuj(playerid, offer_name)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ITEM_USE_AMMO)
	(
		if(response)
		(
			itemid = PlayerCache(playerid)(pManageItem), item_uid = strval(inputtext), weaponid = GetItemID(item_uid), string(128), add_ammo = 0
			if(ItemInfo(weaponid)(iUsed))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Aby załadować broń, nie może być ona w użyciu., OK, )
				return 1
			)
			
			if(!strfind(ItemInfo(itemid)(iName), (PB), true))
			(
				if(strfind(ItemInfo(weaponid)(iName), (PB), true))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz załadować kulek paintballowych do broni., OK, )
					return 1
				)
			)
			
			add_ammo = GetWeaponMaxMag(ItemInfo(weaponid)(iValue1), true) - ItemInfo(weaponid)(iValue2)
			before_load = ItemInfo(weaponid)(iValue2)
						
			if(ItemInfo(itemid)(iValue2) ) add_ammo)
			(
				ItemInfo(weaponid)(iValue2) += add_ammo
				ItemInfo(itemid)(iValue2) -= add_ammo
				mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(weaponid)(iValue2), ItemInfo(weaponid)(iUID))
				mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Sukces !, Załadowaliśmy maksymalną ilość amunicji do twojej broni a reszta pozostała w magazynku., OK, )
			)
			else
			(
				ItemInfo(weaponid)(iValue2) += ItemInfo(itemid)(iValue2)
				ItemInfo(itemid)(iValue2) = 0
				
				mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(weaponid)(iValue2), ItemInfo(weaponid)(iUID))
				mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
				DeleteItem(ItemInfo(itemid)(iUID))
			)

			format(string, sizeof(string), * %s przeładowuje %s., PlayerName(playerid), ItemInfo(weaponid)(iName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			
			printf((ammo) Gracz %s (UID: %d) zaladowal bron %s (UID: %d) Stan amunicji przed: %d, stan amunicji po: %d, PlayerName(playerid), PlayerCache(playerid)(pUID), ItemInfo(weaponid)(iName), item_uid, before_load, ItemInfo(weaponid)(iValue2))

			ApplyAnimation(playerid, COLT45, colt45_reload, 4.0, 0, 0, 0, 0, 0, 1)

			PlayerCache(playerid)(pManageItem) = 0
			return 1
		)
		else
		(
			PlayerCache(playerid)(pManageItem) = 0
			return 1
		)
	)
	if(dialogid == D_OFFER_PRODUCT)
	(
		if(response)
		(
			product_uid, product_number, product_price, product_name(32), customerid = MainPlayerTable(playerid)
			sscanf(inputtext, dxd$ds(32), product_uid, product_number, product_price, product_name)

			OnPlayerSendOffer(playerid, customerid, OFFER_PRODUCT, product_name, product_uid, product_price)

			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_BUY_PRODUCT)
	(
		if(response)
		(
			product_uid, product_number, product_price, product_name(32)
			sscanf(inputtext, dxd$ds(32), product_uid, product_number, product_price, product_name)
			
			product_id = GetProductID(product_uid)
			
			if(GetItemTypeWeight(ProductInfo(product_id)(pType)) ) GetPlayerEqSpace(playerid))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz wystarczająco miejsca w swoim ekwipunku., OK, )
				return 1
			)
			
			/*
					pProductUID,
					pProductPrice,
			*/
			BuyProduct(playerid)(pProductUID) = product_uid
			BuyProduct(playerid)(pProductPrice) = product_price
			
			ShowPlayerDialog(playerid, D_BUY_PAYTYPE, DIALOG_STYLE_MSGBOX, Zakup produktu, Wybierz rodzaj płatności za dany produkt., Gotówka, Karta)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_BUY_PAYTYPE)
	(
		product_id = GetProductID(BuyProduct(playerid)(pProductUID))
		doorid = MainPlayerTable(playerid)
		
		if(response)	// gotówka
		(
			if(PlayerCache(playerid)(pCash) ( BuyProduct(playerid)(pProductPrice))
			(
				BuyProduct(playerid)(pProductUID) = 0
				BuyProduct(playerid)(pProductPrice) = 0
				MainPlayerTable(playerid) = 0
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiedniej ilości gotówki., OK, )
				return 1
			)
			hrp_GivePlayerMoney(playerid, -BuyProduct(playerid)(pProductPrice))
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
		)
		else				// karta
		(
			if(PlayerCache(playerid)(pBankCash) ( BuyProduct(playerid)(pProductPrice))
			(
				BuyProduct(playerid)(pProductUID) = 0
				BuyProduct(playerid)(pProductPrice) = 0
				MainPlayerTable(playerid) = 0
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiedniej ilości pieniędzy na karcie., OK, )
				return 1
			)
			PlayerCache(playerid)(pBankCash) -= BuyProduct(playerid)(pProductPrice)
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
		)
		
		group_cash = floatround(0.90 * BuyProduct(playerid)(pProductPrice))
		group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
		GroupData(group_id_fix)(gCash) += group_cash
		SaveGroup(group_id_fix)
		
		CreatePlayerItem(playerid, ProductInfo(product_id)(pName), ProductInfo(product_id)(pType), ProductInfo(product_id)(pValue1), ProductInfo(product_id)(pValue2))

		ProductInfo(product_id)(pNumber) --
		if(ProductInfo(product_id)(pNumber) ( 1)
		(
			DeleteProduct(product_id)
		)
		else
		(
			SaveProduct(product_id, SAVE_PRODUCT_VALUES)
		)
		
		string(256)
		format(string, sizeof(string), Zakupiono produkt %s.\nKoszt: $%d.\n\nPrzedmiot został dodany do Twojego ekwipunku.\nSkorzystaj z komendy /p, by wyświetlić posiadane przedmioty., ProductInfo(product_id)(pName), BuyProduct(playerid)(pProductPrice))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		
		BuyProduct(playerid)(pProductUID) = 0
		BuyProduct(playerid)(pProductPrice) = 0
		MainPlayerTable(playerid) = 0
		return 1	
	)
	if(dialogid == D_LIST_CONTACTS)
	(
		if(response)
		(
			if(strval(inputtext) (= 0)
			(
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~Nieprawidlowy numer, 3000, 3)
				return 1
			)
			if(strval(inputtext) == 333 || strval(inputtext) == 911 || strval(inputtext) == 777 || strval(inputtext) == 444)
			(
				cmd_tel(playerid, inputtext)
				return 1
			)
			MainPlayerTable(playerid) = strval(inputtext)
			ShowPlayerDialog(playerid, D_OPTION_CONTACT, DIALOG_STYLE_LIST, Opcje kontaktu, 1. Połącz\n2. Wyślij SMS\n3. Usuń kontakt, Wybierz, Anuluj)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_OPTION_CONTACT)
	(
		if(response)
		(
			number = MainPlayerTable(playerid), string(128)
			switch(listitem)
			(
				case 0:
				(
					format(string, sizeof(string), %d, number)
					cmd_tel(playerid, string)
				)
				case 1:
				(
					format(string, sizeof(string), Wprowadź treść wiadomości SMS, którą chcesz wysłać na numer %d., number)
					ShowPlayerDialog(playerid, D_INSERT_TEXT_SMS, DIALOG_STYLE_INPUT, Wyślij SMS, string, Wyślij, Anuluj)
				)
				case 2:
				(
					ShowPlayerDialog(playerid, D_DELETE_CONTACT, DIALOG_STYLE_MSGBOX, Informacja, Jesteś pewien, że chcesz usunąć kontakt %d?\nKontakt zostanie całkowicie usunięty z listy., Tak, Nie)
				)
			)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_DELETE_CONTACT)
	(
		if(response)
		(
			number = MainPlayerTable(playerid), string(128)
			mysql_query_format(DELETE FROM hrp_contacts WHERE contact_number = %d AND contact_ownernumb = %d LIMIT 1, number, PlayerCache(playerid)(pPhoneNumber))
			
			format(string, sizeof(string), Numer %d został usunięty z listy kontaktów., number)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_SEND_VCARD)
	(
		if(response)
		(
			giveplayer_id = strval(inputtext)
			if(!PlayerCache(giveplayer_id)(pPhoneNumber))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ten gracz nie posiada telefonu w użyciu., OK, )
				return 1
			)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_VCARD, vCard, PlayerCache(playerid)(pPhoneNumber), 0)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CHANGE_ROOM_PRICE)
	(
		if(response)
		(
			price = strval(inputtext), string(128)
			if(price ( 0 || strlen(inputtext) ) 11 || price ) 100)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Musisz znajdować się w budynku grupy., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || !IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień do użycia tej funkcji., OK, )
				return 1
			)
			group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
			
			GroupData(group_id_fix)(gValue1) = price
			SaveGroup(group_id_fix)
			
			format(string, sizeof(string), Koszt wynajmu pokoju został pomyślnie zmieniony.\nNowy koszt za wynajem pokoju wynosi: $%d., GroupData(group_id_fix)(gValue1))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TEL_OPTIONS)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					ShowPlayerDialog(playerid, D_INSERT_NUMBER_CALL, DIALOG_STYLE_INPUT, Zadzwoń, Wprowadź numer telefonu komórkowego, na który chcesz zadzwonić., Połącz, Anuluj)
				)
				case 1:
				(
					ShowPlayerDialog(playerid, D_INSERT_NUMBER_SMS, DIALOG_STYLE_INPUT, Wyślij SMS, Wprowadź numer telefonu, na który chcesz wysłać wiadomość SMS., Dalej, Anuluj)
					// JEŻELI TO ODKOMENTUJESZ TO NIE ZAPOMNIJ PRZESTAWIĆ CASEÓW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					// OK PRZESTAWILEM
				)
				case 2:
				(
   	   				list_players(256)
					foreach(Player, i)
					(
						if(IsPlayerConnected(i))
						(
							if(Logged(i) && Spawned(i))
							(
								if(i != playerid)
								(
									if(PlayerToPlayer(5.0, playerid, i))
									(
										format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, i, PlayerName(i))
									)
								)
							)
						)
					)
					if(!strlen(list_players))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znaleziono żadnych graczy w pobliżu., OK, )
					)
					ShowPlayerDialog(playerid, D_SEND_VCARD, DIALOG_STYLE_LIST, Wyślij vCard do:, list_players, Wybierz, Anuluj)
				)
				case 3:
				(
	   				data(128), list_contacts(1024),
						contact_number, contact_name(24)

					mysql_query_format(SELECT contact_number, contact_name FROM hrp_contacts WHERE contact_ownernumb = %d, PlayerCache(playerid)(pPhoneNumber))

					format(list_contacts, sizeof(list_contacts), 911\t\tNumer alarmowy\n333\t\tHurtownia\n777\t\tTaxi\n444\t\tLos Santos News\n-----)

					mysql_store_result()
					while(mysql_fetch_row(data, |))
					(
						sscanf(data, p(|)ds(24), contact_number, contact_name)

						format(list_contacts, sizeof(list_contacts), %s\n%d\t\t%s, list_contacts, contact_number, contact_name)
					)
					mysql_free_result()
					if(strlen(list_contacts) ) 0)
					(
						ShowPlayerDialog(playerid, D_LIST_CONTACTS, DIALOG_STYLE_LIST, Kontakty w telefonie, list_contacts, Wybierz, Anuluj)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znaleziono żadnych kontaktów w telefonie., OK, )
					)
				)
				case 4:
				(
					ShowPlayerDialog(playerid, D_TEL_ADDNUM, DIALOG_STYLE_INPUT, Zapisz numer, Wprowadź numer, który chcesz dodać do kontaktów., Dodaj, Anuluj)
				)
				case 5:
				(
					// Dzwonek w telefonie
					if(PlayerCache(playerid)(pPhoneMuted))
					(
						PlayerCache(playerid)(pPhoneMuted) = false
						GameTextForPlayer(playerid, ~w~Telefon ~g~odciszony, 4000, 6)
					)
					else
					(
						PlayerCache(playerid)(pPhoneMuted) = true
						GameTextForPlayer(playerid, ~w~Telefon ~r~wyciszony, 4000, 6)
					)
				)
				case 6:
				(
	  				itemid = PlayerCache(playerid)(pManageItem)

					ItemInfo(itemid)(iUsed) = 0

					PlayerCache(playerid)(pPhoneNumber) = 0
					GameTextForPlayer(playerid, ~w~Telefon ~r~wylaczony, 4000, 6)

					mysql_query_format(UPDATE hrp_items SET item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUID))
				)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TEL_ADDNUM)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				number
				if(sscanf(inputtext, d, number) || strlen(inputtext) ( 4 || strlen(inputtext) ) 7)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłowy numer telefonu., OK, )
					return 1
				)
				
				if(number == 333 || number == 112 || number == 911 || number == 777 || number == 444 || number == 981 || number == 961 || number == 955)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłowy numer telefonu., OK, )
					return 1
				)
				
				MainPlayerTable(playerid) = number
				ShowPlayerDialog(playerid, D_TEL_ADDNAME, DIALOG_STYLE_INPUT, Zapisz numer, Wprowadź nazwę kontaktu - maksymalnie 24 znaki., OK, )
				return 1
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Musisz wprowadzić numer telefonu jeżeli chcesz dodać kontakt., OK, )
				return 1
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TEL_ADDNAME)
	(
		if(response)
		(
			name(24)
			if(sscanf(inputtext, s(24), name))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową nazwę kontaktu., OK, )
			)
			
			mysql_query_format(INSERT INTO hrp_contacts (contact_number, contact_name, contact_ownernumb) VALUES (%d, %s, %d), MainPlayerTable(playerid), inputtext, PlayerCache(playerid)(pPhoneNumber))

			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Zapisz numer, Nowy kontakt został dodany do listy. Użyj /tel, by sprawdzić listę kontaktów., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_INSERT_NUMBER_CALL)
	(
		if(response)
		(
			string(12)
			if(strval(inputtext) (= 0 || strlen(inputtext) ) 7)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłowy numer telefonu., OK, )
				return 1
			)
			format(string, sizeof(string), %d, strval(inputtext))
			cmd_tel(playerid, string)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_INSERT_NUMBER_SMS)
	(
		if(response)
		(
			number = strval(inputtext), string(128)
			if(strval(inputtext) (= 0 || strlen(inputtext) ) 7)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłowy numer telefonu., OK, )
				return 1
			)
			
			if(number ) 999999 || number ( 100000)
			(
				GuiMsg(playerid, Wiadomości tekstowe możesz wysyłać wyłącznie na telefony komórkowe.\nSprawdź czy wpisałeś dobry numer., 1)
				return 1
			)
			
			MainPlayerTable(playerid) = number
			
   			format(string, sizeof(string), Wprowadź treść wiadomości SMS, którą chcesz wysłać na numer %d., number)
	 		ShowPlayerDialog(playerid, D_INSERT_TEXT_SMS, DIALOG_STYLE_INPUT, Wyślij SMS, string, Wyślij, Anuluj)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_INSERT_TEXT_SMS)
	(
		if(response)
		(
			number = MainPlayerTable(playerid), string(256)
			format(string, sizeof(string), %d %s, number, inputtext)
			
			cmd_sms(playerid, string)
			
			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_SELECT_WEIGHT_BENCH)
	(
		if(response)
		(
			if(GetPlayerVirtualWorld(playerid) != 0)
			(
				if(!PlayerCache(playerid)(pTrainTime))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Musisz wykupić pozwolenie na używanie obiektów u pracownika., OK, )
					return 1
				)
			)
			weight = strval(inputtext), object_id = PlayerCache(playerid)(pGymObject),
				Float:strength = PlayerCache(playerid)(pStrength)

			if(strength (= 10 && weight )= 80 || strength (= 30 && weight )= 140 || strength (= 50 && weight )= 180 || strength (= 70 && weight )= 220)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Twoja postać jest zbyt słaba na unoszenie takich ciężarów., OK, )
				return 1
			)

			PlayerCache(playerid)(pGymValue1) = weight
			PlayerCache(playerid)(pGymValue2) = 0
			
			if(PlayerCache(playerid)(pStrength) ( 50)
			(
				PlayerCache(playerid)(pGymValue1) *= 2
			)
			
  			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(PlayerCache(i)(pGymType) == TRAIN_BENCH_PRESS)
					(
						if(PlayerCache(i)(pGymObject) == object_id)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ktoś aktualnie korzysta z tego obiektu., OK, )
							return 1
						)
					)
				)
			)
		 	Float:ObjPosX, Float:ObjPosY, Float:ObjPosZ,
				Float:ObjRotX, Float:ObjRotY, Float:ObjRotZ

			GetDynamicObjectPos(object_id, ObjPosX, ObjPosY, ObjPosZ)
			GetDynamicObjectRot(object_id, ObjRotX, ObjRotY, ObjRotZ)

			GetXYInFrontOfObject(object_id, ObjPosX, ObjPosY, 1.0)

			SetPlayerPos(playerid, ObjPosX, ObjPosY, ObjPosZ + 1.0)
			SetPlayerFacingAngle(playerid, ObjRotZ)

			ApplyAnimation(playerid, BENCHPRESS, gym_bp_geton, 4.0, 0, 0, 0, 1, 0, 1)

			PlayerCache(playerid)(pGymType) = TRAIN_BENCH_PRESS
			SetTimerEx(OnPlayerGymTrainStarted, 3500, 0, d, playerid)
			
			if(GetPlayerVirtualWorld(playerid) == 0)
			(
				PlayerCache(playerid)(pTrainTime) = 600
			)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Trening rozpoczęty, Rozpocząłeś trening na ławce wyciskanej, przeczytaj instrukcję zanim zaczniesz wyciskać!\n\nUżywaj klawiszy GÓRA oraz DÓŁ aby unosić oraz opuszczać sztangę.\nAby zakończyć trening, wciśnij klawisz ENTER.\n\nAby trening przebiegł poprawnie i bez skutków ubocznych, staraj się regularnie unosić i opuszczać sztangę., OK, )
			return 1
		)
		else
		(
			PlayerCache(playerid)(pGymObject) = INVALID_OBJECT_ID
			return 1
		)
	)
	if(dialogid == D_SELECT_WEIGHT_BARBELL)
	(
		if(response)
		(
   			if(!PlayerCache(playerid)(pTrainTime))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Musisz wykupić pozwolenie na używanie obiektów u pracownika., OK, )
				return 1
			)
			weight = strval(inputtext), object_id = PlayerCache(playerid)(pGymObject),
				Float:strength = PlayerCache(playerid)(pStrength)

			if(strength (= 30 && weight )= 80 || strength (= 70 && weight )= 120 || strength (= 90 && weight )= 140)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Twoja postać jest zbyt słaba na unoszenie takich ciężarów., OK, )
				return 1
			)

			PlayerCache(playerid)(pGymValue1) = weight
			PlayerCache(playerid)(pGymValue2) = 0

			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(PlayerCache(i)(pGymType) == TRAIN_BARBELL)
					(
						if(PlayerCache(i)(pGymObject) == object_id)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ktoś aktualnie korzysta z tego obiektu., OK, )
							return 1
						)
					)
				)
			)
	 		Float:ObjPosX, Float:ObjPosY, Float:ObjPosZ,
				Float:ObjRotX, Float:ObjRotY, Float:ObjRotZ

			GetDynamicObjectPos(object_id, ObjPosX, ObjPosY, ObjPosZ)
			GetDynamicObjectRot(object_id, ObjRotX, ObjRotY, ObjRotZ)

			GetXYInFrontOfObject(object_id, ObjPosX, ObjPosY, 1.0)

			SetPlayerPos(playerid, ObjPosX, ObjPosY, ObjPosZ + 1.0)
			SetPlayerFacingAngle(playerid, ObjRotZ)
			
			ApplyAnimation(playerid, FREEWEIGHTS, gym_free_pickup, 4.0, 0, 0, 0, 1, 0, 1)

			PlayerCache(playerid)(pGymType) = TRAIN_BARBELL
			SetTimerEx(OnPlayerGymTrainStarted, 2000, 0, d, playerid)
			
			if(GetPlayerVirtualWorld(playerid) == 0)
			(
				PlayerCache(playerid)(pTrainTime) = 600
			)
			
			return 1
		)
		else
		(
			PlayerCache(playerid)(pGymObject) = INVALID_OBJECT_ID
			return 1
		)
	)
	if(dialogid == D_SELECT_FIGHTING_STYLE)
	(
		if(response)
		(
			if(!PlayerCache(playerid)(pTrainTime))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Musisz wykupić pozwolenie na używanie obiektów u pracownika., OK, )
				return 1
			)
			
			PlayerCache(playerid)(pGymValue1) = 0
			
			switch(listitem)
			(
				case 0:
				(
					if(PlayerCache(playerid)(pStrength) ) 20.0)
					(
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING)
						PlayerCache(playerid)(pGymValue2) = 65
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Siła Twojej postaci jest zbyt mała aby trenować Boxing., OK, )
						return 1
					)
				)
				case 1:
				(
					if(PlayerCache(playerid)(pStrength) ) 20.0)
					(
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU)
						PlayerCache(playerid)(pGymValue2) = 30
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Siła Twojej postaci jest zbyt mała aby trenować Kung Fu., OK, )
						return 1
					)
				)
				case 2:
				(
					if(PlayerCache(playerid)(pStrength) ) 20.0)
					(
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK)
						PlayerCache(playerid)(pGymValue2) = 30
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, \W tych butach nie wejdziesz. Nie ma wjazdu dla dresiarzy.\ ~ Roman Bugaj (Szczęka), OK, )
						return 1
					)
				)
			)
			
			PlayerCache(playerid)(pGymType) = TRAIN_PUNCH_BAG
			OnPlayerGymTrainStarted(playerid)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Uderzaj w worek treningowy, by nauczyć się nowego stylu.\n\nJeżeli nie zmieścisz się w czasie, styl walki nie zapisze się,\na trening będziesz musiał rozpocząć na nowo.\n\nBądź cały czas skierowany w stronę worka treningowego,\nw przeciwnym wypadku, trafienia nie będą naliczać się., OK, )
			return 1
		)
		else
		(
			PlayerCache(playerid)(pGymObject) = INVALID_OBJECT_ID
			return 1
		)
	)
	if(dialogid == D_ADD_CHIT)
	(
		if(response)
		(
			itemid = PlayerCache(playerid)(pManageItem), chit_desc(128), string(128),
				chit_uid
				
			if(strlen(inputtext) (= 0)
			(
		 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Pole tekstowe nie może być puste!, OK, )
				PlayerCache(playerid)(pManageItem) = 0
				return 1
			)
			if(strlen(inputtext) ) 64)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Tekst nie może przekroczyć ciągu 64 znaków., OK, )
				PlayerCache(playerid)(pManageItem) = 0
				return 1
			)
			mysql_real_escape_string(inputtext, chit_desc)
			mysql_query_format(INSERT INTO hrp_chits (chit_desc, chit_writer, chit_datetime) VALUES (%s, %s, NOW()), chit_desc, PlayerName(playerid))

			chit_uid = mysql_insert_id()

			CreatePlayerItem(playerid, Karteczka, ITEM_CHIT, chit_uid, 0)

			ItemInfo(itemid)(iValue1) --
			PlayerCache(playerid)(pManageItem) = 0

			if(ItemInfo(itemid)(iValue1) ) 0)
			(
				mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
			)
			else
			(
				DeleteItem(ItemInfo(itemid)(iUID))
			)
			
			format(string, sizeof(string), * %s wyrywa karteczkę z notesu., PlayerName(playerid))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Treść została pomyślnie zapisana na karteczce.\nKarteczka pojawiła się w Twoim ekwipunku., OK, )
			return 1
		)
		else
		(
			PlayerCache(playerid)(pManageItem) = 0
			return 1
		)
	)
	if(dialogid == D_UNMOUNT_TUNING)
	(
		if(response)
		(
			item_uid, componentid, vehid = GetPlayerVehicleID(playerid)
			sscanf(inputtext, dd, item_uid, componentid)
			
			mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d, item_vehuid = 0 WHERE item_uid = %d LIMIT 1, PLACE_PLAYER, PlayerCache(playerid)(pUID), item_uid)
			
			LoadItem(item_uid)
			
			hrp_RemoveVehicleComponent(vehid, componentid)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Część została odmontowana pomyślnie.\nOdmontowaną część znajdziesz w swoim ekwipunku., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CREATE_BANK_ACCOUNT)
	(
		if(response)
		(
			bank_number = 100000000 + random(999999999), string(128)
			PlayerCache(playerid)(pBankNumber) = bank_number
			
			format(string, sizeof(string), Konto bankowe zostało założone pomyślnie.\nTwój nowy numer konta: %d., PlayerCache(playerid)(pBankNumber))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_BANK_OPTION)
	(
		if(response)
		(
			string(256)
			switch(listitem)
			(
				case 0:
				(
					format(string, sizeof(string), Numer konta:\t%d\nStan konta:\t$%d, PlayerCache(playerid)(pBankNumber), PlayerCache(playerid)(pBankCash))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Konto bankowe, string, OK, )
				)
				case 1:
				(
					if(PlayerCache(playerid)(pBankLastTransaction) + (60*15) ( gettime())
					(
						ShowPlayerDialog(playerid, D_WITHDRAW_CASH, DIALOG_STYLE_INPUT, Konto bankowe » Wypłać gotówkę, Wprowadź kwotę jaką chcesz wypłacić z konta bankowego., Wypłać, Anuluj)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Bank pozwala na wypłatę bankomatową raz na 15 minut., OK, )
					)
				)
				case 2:
				(
					ShowPlayerDialog(playerid, D_DEPOSIT_CASH, DIALOG_STYLE_INPUT, Konto bankowe » Wpłać gotówkę, Wprowadź kwotę jaką chcesz wpłacić na swoje konto bankowe., Wpłać, Anuluj)
				)
				case 3:
				(
				
				)
				case 4:
				(
					/*if(PlayerCache(playerid)(pAdmin) == 0)
					(
						GuiMsg(playerid,Funkcja tymczasowo zablokowana.,1)
						return 1
					)*/
					if(PlayerCache(playerid)(pGamePoints) ( 100)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz dokonywać przelewów, nie majac 100GS., OK, )
						return 1
					)
					ShowPlayerDialog(playerid, D_TRANSFER_NUMBER, DIALOG_STYLE_INPUT, Konto bankowe » Dokonaj przelewu, Wprowadź numer konta bankowego, na który chcesz przelać gotówkę., Dalej, Anuluj)
				)
			)
			ApplyAnimation(playerid,INT_SHOP,shop_cashier,4.0,0,0,0,0,0,0)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DEPOSIT_CASH)
	(
		if(response)
		(
			deposit_cash = strval(inputtext), string(128)
			if(strlen(inputtext) ) 11 || deposit_cash (= 0 || deposit_cash ) PlayerCache(playerid)(pCash))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
   			hrp_GivePlayerMoney(playerid, -deposit_cash)
			PlayerCache(playerid)(pBankCash) += deposit_cash
			
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			format(string, sizeof(string), Na konto bankowe wpłacono kwotę $%d.\nNowy stan konta: $%d, deposit_cash, PlayerCache(playerid)(pBankCash))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			hrp_MoneyActionLog(%s (UID: %d) wplacil $%d na swoje konto bankowe (bank: $%d, portfel: $%d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), deposit_cash, PlayerCache(playerid)(pBankCash), PlayerCache(playerid)(pCash))
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_WITHDRAW_CASH)
	(
		if(response)
		(
			withdraw_cash = strval(inputtext), string(128)
			if(strlen(inputtext) ) 11 || withdraw_cash (= 0 || withdraw_cash ) PlayerCache(playerid)(pBankCash))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			PlayerCache(playerid)(pBankCash) -= withdraw_cash
			hrp_GivePlayerMoney(playerid, withdraw_cash)
			
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			format(string, sizeof(string), Z konta bankowego wypłacono kwotę $%d.\nNowy stan konta: $%d, withdraw_cash, PlayerCache(playerid)(pBankCash))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			PlayerCache(playerid)(pBankLastTransaction) = gettime()

			hrp_MoneyActionLog(%s (UID: %d) wyplacil $%d ze swojego konta bankowego (bank: $%d, portfel: $%d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), withdraw_cash, PlayerCache(playerid)(pBankCash), PlayerCache(playerid)(pCash))
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TRANSFER_NUMBER)
	(
		if(response)
		(
			// Anty bugowanie znowu -.-
			bool:passed = false
			if(gettime() - LogTime(playerid) ) 60)
				passed = true
				
			if(!passed)
			(
				GuiMsg(playerid, Musisz chwilę odczekać nim będziesz mógł przelać pieniądze., 0)
				return 1
			)
			
			bank_number = strval(inputtext), data(32),
				char_uid, char_gid
				
			if(strlen(inputtext) ) 10 || strlen(inputtext) ( 9)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłowy numer konta bankowego., OK, )
				return 1
			)
			mysql_query_format(SELECT char_uid, char_gid FROM hrp_characters WHERE char_banknumb = %d LIMIT 1, bank_number)
			
			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)dd, char_uid, char_gid)
			)
			else
			(
				char_uid = -1
				char_gid = -1
			)
			mysql_free_result()
			
			if(char_uid == -1 || char_gid == -1)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił bład, Wprowadzono nieprawidłowy numer konta bankowego., OK, )
				return 1
			)
			if(char_uid == PlayerCache(playerid)(pUID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz przelewać pieniędzy na własne konto bankowe., OK, )
				return 1
			)
			if(char_gid == PlayerCache(playerid)(pGID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz przelewać pieniędzy między własnymi postaciami!, OK, )
				return 1
			)
			MainPlayerTable(playerid) = char_uid
			SecondPlayerTable(playerid) = bank_number
			
			printf((CROTOLOLO) Gracz %s (uid: %d) wpisal numer %d nalezacy do gracza uid %d do przelewu., PlayerName(playerid), PlayerCache(playerid)(pUID), bank_number, char_uid)
			ShowPlayerDialog(playerid, D_TRANSFER_CASH, DIALOG_STYLE_INPUT, Wprowadź kwotę, Wprowadź kwotę, jaką chcesz przelać na wybrane konto bankowe.\n\nUWAGA!\nGotówka jest pobierana bezpośrednio ze stanu konta bankowego, nie z portfela!, Przelej, Anuluj)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TRANSFER_CASH)
	(
		if(response)
		(
			transfer_cash = strval(inputtext), char_uid = MainPlayerTable(playerid), account = SecondPlayerTable(playerid), giveplayer_id = GetPlayerID(char_uid), string(128)
			if(strlen(inputtext) ) 11 || transfer_cash (= 0 || transfer_cash ) PlayerCache(playerid)(pBankCash) || transfer_cash (= 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			if(giveplayer_id != INVALID_PLAYER_ID && Logged(giveplayer_id) && Spawned(giveplayer_id))
			(
				PlayerCache(giveplayer_id)(pBankCash) += transfer_cash
				format(string, sizeof(string), Na twoje konto bankowe wpłynęła właśnie kwota $%d., transfer_cash)
				SendClientMessage(giveplayer_id, 0xFFD700CC, string)
			)
			else
			(
				format(string, sizeof(string), otrzymałeś przelew w wysokości $%d!, transfer_cash)
				AddPlayerOfflineMessage(char_uid, string)
				
   				mysql_query_format(UPDATE hrp_characters SET char_bankcash = char_bankcash + %d WHERE char_uid = %d LIMIT 1, transfer_cash, char_uid)
				mysql_query_format(UPDATE hrp_characters SET char_color = (((((char_cash + char_bankcash) + 31) * 3) + char_uid) + 3) WHERE char_uid = %d LIMIT 1, char_uid)
			)

			printf((CROTOLOLO) Gracz %s (uid: %d) przelal $%d do gracza uid %d., PlayerName(playerid), PlayerCache(playerid)(pUID), transfer_cash, char_uid)
			
			PlayerCache(playerid)(pBankCash) -= transfer_cash
			MainPlayerTable(playerid) = 0
			
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			format(string, sizeof(string), Pieniądze zostały pomyślnie przelane na konto %d.\nPrzelana ilość gotówki: %d\n\nGotówka została pobrana z Twojego konta bankowego., account, transfer_cash)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			hrp_MoneyActionLog(%s (UID: %d) przelal $%d dla gracza (UID: %d) (bank: $%d, portfel: $%d), PlayerRealName(playerid), PlayerCache(playerid)(pUID), transfer_cash, char_uid, PlayerCache(playerid)(pBankCash), PlayerCache(playerid)(pCash))
			
			PlayerCache(playerid)(pFlood) = 2
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			SecondPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_WRITE_A_CHECK)
	(
		if(response)
		(
			itemid = PlayerCache(playerid)(pManageItem), check_price = strval(inputtext), string(128), item_name(32)
			if(strlen(inputtext) ) 11 || check_price (= 0 || check_price ) PlayerCache(playerid)(pBankCash) || check_price (= 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			PlayerCache(playerid)(pBankCash) -= check_price
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			format(item_name, sizeof(item_name), Czek na $%d, check_price)
			CreatePlayerItem(playerid, item_name, ITEM_CHECK, check_price, 0)
			
			ItemInfo(itemid)(iValue1) --
			PlayerCache(playerid)(pManageItem) = 0

			if(ItemInfo(itemid)(iValue1) ) 0)
			(
				mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
			)
			else
			(
				DeleteItem(ItemInfo(itemid)(iUID))
			)
			
 			format(string, sizeof(string), * %s wypisuje czek na $%d., PlayerName(playerid), check_price)
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Czek został wypisany pomyślnie.\nPieniądze zostały pobrane z Twojego konta bankowego i wypisane na czeku., OK, )
			return 1
		)
		else
		(
			PlayerCache(playerid)(pManageItem) = 0
			return 1
		)
	)
	if(dialogid == D_PRODUCT_TYPE)
	(
		if(response)
		(
			doorid = MainPlayerTable(playerid), data(128), list_orders(1024), order_owner,
				order_uid, order_type = strval(inputtext), order_price, order_name(32)
				
			if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
			(
				group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
				order_owner = GroupData(group_id_fix)(gType)
			)
			else if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
			(
				order_owner = 0
			)
			mysql_query_format(SELECT order_uid, order_price, order_name FROM hrp_orders WHERE order_type = %d AND order_ownertype = %d AND order_owner = %d OR order_type = %d AND order_ownertype = 0 AND order_owner = %d, order_type, DoorData(doorid)(dOwnerType), order_owner, order_type, DoorData(doorid)(dOwner))
			
			mysql_store_result()
			while(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)dds(32), order_uid, order_price, order_name)
				format(list_orders, sizeof(list_orders), %s\n%d\t$%d\t%s, list_orders, order_uid, order_price, order_name)
			)
			if(strlen(list_orders))
			(
				ShowPlayerDialog(playerid, D_SELECT_PRODUCT, DIALOG_STYLE_LIST, Wybierz produkt z tego typu:, list_orders, Wybierz, Anuluj)
			)
			else
			(
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Brak dostepu, 3000, 3)
				
	   			MainPlayerTable(playerid) = 0

				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
				RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			)
			mysql_free_result()
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_SELECT_PRODUCT)
	(
		if(response)
		(
			string(128)
			sscanf(inputtext, d$ds(32), OrderProductUID(playerid), OrderProductPrice(playerid), OrderProductName(playerid))

			format(string, sizeof(string), Wprowadź ile produktów tego typu chcesz zamówić.\n\nWybrano produkt: %s\nKoszt za sztukę: $%d, OrderProductName(playerid), OrderProductPrice(playerid))
			ShowPlayerDialog(playerid, D_PRODUCT_NUMBER, DIALOG_STYLE_INPUT, Ilość sztuk, string, Dalej, Anuluj)
			return 1
		)
		else
		(
	 		MainPlayerTable(playerid) = 0

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_PRODUCT_NUMBER)
	(
		if(response)
		(
	 		product_number = strval(inputtext), string(128)
			// tutaj zamiast 11 to 5 żeby lepiej było, bo sie bugowalo do miliardów ...
			if(strlen(inputtext) ) 5 || product_number (= 0)
			(
				format(string, sizeof(string), Wprowadź ile produktów tego typu chcesz zamówić.\n\nWybrano produkt: %s\nKoszt za sztukę: $%d, OrderProductName(playerid), OrderProductPrice(playerid))
				ShowPlayerDialog(playerid, D_PRODUCT_NUMBER, DIALOG_STYLE_INPUT, Ilość sztuk, string, Dalej, Anuluj)
				
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Nieprawidlowa liczba, 3000, 3)
				return 1
			)
			if(PlayerCache(playerid)(pCash) ( OrderProductPrice(playerid) * product_number)
			(
				format(string, sizeof(string), Wprowadź ile produktów tego typu chcesz zamówić.\n\nWybrano produkt: %s\nKoszt za sztukę: $%d, OrderProductName(playerid), OrderProductPrice(playerid))
				ShowPlayerDialog(playerid, D_PRODUCT_NUMBER, DIALOG_STYLE_INPUT, Ilość sztuk, string, Dalej, Anuluj)

				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Nie posiadasz tyle gotowki, 3000, 3)
				return 1
			)
			OrderProductNumber(playerid) = product_number
			ShowPlayerDialog(playerid, D_PRODUCT_PRICE, DIALOG_STYLE_INPUT, Koszt produktu, Wprowadź oferowaną cenę produktu.\nCena jaką wprowadzisz będzie pobierana za zakup produktu w Twojej instytucji.\n\nCena powinna być wyższa niż hurtowa, byś miał profit z wyprzedanych produktów.\nKoszt danego przedmiotu możesz w każdej chwili zmienić dzięki komendzie /drzwi opcje., Zamów, Anuluj)
			return 1
		)
		else
		(
	 		MainPlayerTable(playerid) = 0

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_PRODUCT_PRICE)
	(
		if(response)
		(
			price = strval(inputtext), doorid = MainPlayerTable(playerid)
			if(price (= 0 || strlen(inputtext) )= 10)
			(
				ShowPlayerDialog(playerid, D_PRODUCT_PRICE, DIALOG_STYLE_INPUT, Koszt produktu, Wprowadź oferowaną cenę produktu.\nCena jaką wprowadzisz będzie pobierana za zakup produktu w Twojej instytucji.\n\nCena powinna być wyższa niż hurtowa, byś miał profit z wyprzedanych produktów.\nKoszt danego przedmiotu możesz w każdej chwili zmienić dzięki komendzie /drzwi opcje., Zamów, Anuluj)
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Nie posiadasz tyle gotowki, 3000, 3)
				return 1
			)
  			data(24), order_price = OrderProductPrice(playerid) * OrderProductNumber(playerid),
				order_itemtype, order_itemvalue1, order_itemvalue2, order_secured, order_limited

			// Jednak weźmiemy mu o 40% mniej gotówki, niech zarobi
			if(OrderProductNumber(playerid) )= 20)
			(
				order_price = floatround(order_price * 0.6)
			)

			mysql_query_format(SELECT order_itemtype, order_itemvalue1, order_itemvalue2, order_secured, order_limited FROM hrp_orders WHERE order_uid = %d LIMIT 1, OrderProductUID(playerid))

			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)ddddd, order_itemtype, order_itemvalue1, order_itemvalue2, order_secured, order_limited)
			)
			mysql_free_result()

			if(order_secured)
			(
				if(!order_limited)
				(
					// SprawdY, czy paczka czasem nie dochodzi
					foreach(Packages, package_id)
					(
						if(PackageInfo(package_id)(pUID))
						(
							if(PackageInfo(package_id)(pSecured))
							(
								if(PackageInfo(package_id)(pDoorUID) == DoorData(doorid)(dUID))
								(
									SendClientMessage(playerid, COLOR_DO, * Nie można połączyć się z wybranym numerem...) // SELER
								
				 					MainPlayerTable(playerid) = 0

									SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
									RemovePlayerAttachedObject(playerid, SLOT_PHONE)
									return 1
								)
							)
						)
					)
				)	
				if(order_limited)
				(
					// Sprawdz czy przypadkiem nie wykorzystali limitu broni (10bronie/25ammo)
					group_id_fix = DoorData(doorid)(dOwner)
					order_amount = OrderProductNumber(playerid)
					weaporders_now, ammoorders_now, calc_orders
					mysql_query_format(SELECT weap_orders, ammo_orders FROM hrp_groups WHERE group_uid = %d, group_id_fix)
					mysql_store_result()
					while(mysql_fetch_row(data, |))
					(
						sscanf(data, p(|)dd, weaporders_now, ammoorders_now)
					)
					mysql_free_result()
					if(order_itemtype == 6) // bronie
					(
						calc_orders = weaporders_now + order_amount
						if(calc_orders )= 11)
						(
							SendClientMessage(playerid, COLOR_DO, * Nie można połączyć się z wybranym numerem...) // SELER	

							MainPlayerTable(playerid) = 0

							SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
							RemovePlayerAttachedObject(playerid, SLOT_PHONE)
							return 1
						)
					)
					else // reszta(czyli ammo)
					(
						calc_orders = ammoorders_now + order_amount
						if(calc_orders )= 26)
						(
							SendClientMessage(playerid, COLOR_DO, * Nie można połączyć się z wybranym numerem...) // SELER	

							MainPlayerTable(playerid) = 0

							SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
							RemovePlayerAttachedObject(playerid, SLOT_PHONE)
							return 1
						)
					)

					// SprawdY, czy paczka czasem nie dochodzi
					foreach(LimitedPackages, limitedpackage_id)
					(
						if(LimitedPackageInfo(limitedpackage_id)(pUID))
						(
							if(LimitedPackageInfo(limitedpackage_id)(pSecured))
							(
								if(LimitedPackageInfo(limitedpackage_id)(pDoorUID) == DoorData(doorid)(dUID))
								(
									SendClientMessage(playerid, COLOR_DO, * Nie można połączyć się z wybranym numerem...) // SELER
								
				 					MainPlayerTable(playerid) = 0

									SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
									RemovePlayerAttachedObject(playerid, SLOT_PHONE)
									return 1
								)
							)
						)
					)
					// seler
					CreateLimitedPackage(DoorData(doorid)(dUID), playerid, PlayerCache(playerid)(pUID), OrderProductName(playerid), order_itemtype, order_itemvalue1, order_itemvalue2, OrderProductNumber(playerid), price, order_secured)
					SendClientMessage(playerid, COLOR_YELLOW, (Telefon) (Głos męski): Spotkajmy się, skontaktuj się z moim pośrednikiem jak będziesz na miejscu.) // SELER
					SendClientMessage(playerid, COLOR_YELLOW, Rozmowa została zakonczońa.)
					SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Zadzwoń pod ten numer jak będziesz na miejscu.)
					if(order_itemtype == 6) // bronie
					(
						mysql_query_format(UPDATE hrp_groups SET weap_orders = weap_orders + %i WHERE group_uid = %i LIMIT 1, order_amount, group_id_fix)
					)
					else // reszta(czyli ammo)
					(
						mysql_query_format(UPDATE hrp_groups SET ammo_orders = ammo_orders + %i WHERE group_uid = %i LIMIT 1, order_amount, group_id_fix)
					)
				)
				else
				(
					SendClientMessage(playerid, COLOR_YELLOW, (Telefon) (Głos męski): Okej, niedługo Wam to przywiozę.) // SELER
					SendClientMessage(playerid, COLOR_YELLOW, Rozmowa została zakończona.)
					CreatePackage(DoorData(doorid)(dUID), OrderProductName(playerid), order_itemtype, order_itemvalue1, order_itemvalue2, OrderProductNumber(playerid), price, order_secured)
				)
			)
			else
			(
				SendClientMessage(playerid, COLOR_YELLOW, Sekretarka: Dziekujemy za złożenie zamówienia, paczka zaczeka u nas w hurtowni.)
				CreatePackage(DoorData(doorid)(dUID), OrderProductName(playerid), order_itemtype, order_itemvalue1, order_itemvalue2, OrderProductNumber(playerid), price, order_secured)
			)
			
			hrp_GivePlayerMoney(playerid, -order_price)

			MainPlayerTable(playerid) = 0

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
		else
		(
   			MainPlayerTable(playerid) = 0

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_HELP)
	(
		if(response)
		(
			help_type(32)
			sscanf(inputtext, »s(32), help_type)
			
			if(!strcmp(help_type, Wprowadzenie, true))
			(
			 	ShowPlayerDialog(playerid, D_INTRODUCTION, DIALOG_STYLE_MSGBOX, Wprowadzenie (1/2), Witaj na serwerze SERVER_NAME.\n\nPojawiłeś się w metrze Los Santos, na mieście znajdziesz wiele różnego rodzaju\ninstytucji, dzięki którym będziesz mógł przyjąć się do pracy\na także skorzystać z ich usług np. kupić telefon, bądź zjeść obiad.\n\nNa pierwszy etat udaj się do urzędu miasta, by wyrobić dokumenty niezbędne do gry., Dalej, Zamknij)
			  	// ShowPlayerDialog(playerid, D_INTRODUCTION, DIALOG_STYLE_MSGBOX, Wprowadzenie (1/2), Witaj na serwerze SERVER_NAME.\n\nPojawiłeś się w metrze Los Santos, znajdziesz tutaj wiele różnego rodzaju\ninstytucji, dzięki którym będziesz mógł przyjąć się do pracy\na także skorzystać z ich usług np. kupić telefon, bądź zjeść obiad.\n\nNa pierwszy etat udaj się do urzędu miasta, by wyrobić dokumenty niezbędne do gry., Dalej, Zamknij)
				return 1
			)
			if(!strcmp(help_type, Komendy główne, true))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Pomoc » Komendy główne, (/p)rzedmiot, (/o)feruj, (/tel)efon, (/od)bierz, (/z)akoncz, /sms\n/stats, (/a)dmins, /kup, /pokoj, /opis, /bank, /id, /pokaz, /tog\n/pay, (/anim)acje, /wyrzuc, /report, /tankuj, /qs, /przebierz, /bus\n\nRodzaje czatów:\n(/k)rzycz, /l, /b, /me, /do, /w, /re, /m, OK, Zamknij)
				return 1
			)
			if(!strcmp(help_type, Pojazd, true))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Pomoc » Pojazd, Własne cztery kółka możesz nabyć w salonach samochodowych,\nmusisz tylko porozmawiać z ich pracownikiem i odegrać krótką interakcję.\n\nPo zaakceptowaniu oferty złożonej przez pracownika, pojazd\npowinien pojawić się w magazynie, a na mapie będziesz widział jego położenie.\n\nKomendy dla pojazdu:\n/pojazd (lista, namierz, zaparkuj, tuning, przypisz, zamknij, info), OK, Zamknij)
				return 1
			)
			if(!strcmp(help_type, Przedmioty, true))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Pomoc » Przedmioty, Aby zarządzać swoimi przedmiotami w ekwipunku, uzyj komendy /p.\nPo wybraniu dowolnego z przedmiotów, ujrzysz listę dosepnych akcji dla wybranego przedmiotu.\n\nJeżeli jednak pragniesz szybko użyć przedmiotu, użyj komendy /u\na następnie wybierz przedmiot, który chcesz użyć. Możesz również\nskorzystać ze skrótu: /u (UID przedmiotu) (Dodatkowe parametry)\n\nPrzykład:\n/u 1998 z kabury., OK, Zamknij)
				return 1
			)
			if(!strcmp(help_type, Praca, true))
			(
				string(1024)
				format(string, sizeof(string), Praca, dzięki której będziesz mógł zarobić trochę pieniędzy jest zależna od Twojej wyobraźni,\naby jednak znaleźć pracę musisz pochodzić po instytucjach w celu poznania konkretnych szczegółów.\n\nMożesz pracować jednocześnie w biznesie, frakcji oraz organizacji,\n)
				format(string, sizeof(string), %s jakby tego było mało, możesz też posiadać pracę dorywczą, którą znajdziesz w urzędzie miasta.\n\n/paczka - odbieranie paczki z hurtowni/dostarczanie paczki do biznesu.\n/paczka anuluj - anulowanie dostarczania paczki.\n/sprzatacz - uruchomienie pracy sprzątacza ulic (musisz być w Sweeprze).\n/o montaz - montowanie części tuningowych.\n/o naprawe - oferowanie naprawy pojazdu.\n/o hotdog - oferowanie hotdoga (musisz znajdować się przy budce z hotdogami)., string)
			 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Pomoc » Praca, string, OK, Zamknij)
				return 1
			)
			if(!strcmp(help_type, Grupy, true))
			(
				// ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Pomoc » Grupy, Jako przeciętny gracz, masz pięć slotów przeznaczonych dla grup
				return 1
			)
			if(!strcmp(help_type, Administracja, true))
			(
				return 1
			)
			if(!strcmp(help_type, Support, true))
			(
				return 1
			)
			if(!strcmp(help_type, Grupy, true))
			(
				return 1
			)
			if(!strcmp(help_type, Animacje, true))
			(
				cmd_anim(playerid, )
				return 1
			)
			return 1
		)
		else
		(
		
			return 1
		)
	)
	if(dialogid == D_SEND_PW)
	(
		if(response)
		(
			giveplayer_id = MainPlayerTable(playerid), string(256)
			inputtext(0) = chrtoupper(inputtext(0))
			
			format(string, sizeof(string), %d %s, giveplayer_id, inputtext)
			cmd_w(playerid, string)
			
			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_PLAY_ANIM)
	(
		if(response)
		(
			anim_id = listitem + 1
			if(!AnimInfo(anim_id)(aAction))
			(
				ApplyAnimation(playerid, AnimInfo(anim_id)(aLib), AnimInfo(anim_id)(aName), AnimInfo(anim_id)(aSpeed), AnimInfo(anim_id)(aOpt1), AnimInfo(anim_id)(aOpt2), AnimInfo(anim_id)(aOpt3), AnimInfo(anim_id)(aOpt4), AnimInfo(anim_id)(aOpt5), 1)

				TextDrawSetString(Text:TextDrawMainInfo(playerid), ~g~PPM ~w~anuluje gre animacji.)
				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
				
				PlayerCache(playerid)(pShowInfoText) = 5
			)
			else
			(
				SetPlayerSpecialAction(playerid, AnimInfo(anim_id)(aAction))

				TextDrawSetString(Text:TextDrawMainInfo(playerid), ~g~~k~~VEHICLE_ENTER_EXIT~ ~w~anuluje gre animacji.)
				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

				PlayerCache(playerid)(pShowInfoText) = 5
			)
			PlayerCache(playerid)(pPlayAnim) = true
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_GET_PACKAGE)
	(
		if(response)
		(
			package_uid = strval(inputtext), package_id = GetPackageID(package_uid), string(128)
			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(PlayerCache(i)(pPackageUID) == package_uid)
					(
						format(string, sizeof(string), Ta paczka jest aktualnie dostarczana przez %s., PlayerName(i))
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, string, OK, )
						return 1
					)
				)
			)
			doorid = GetDoorID(PackageInfo(package_id)(pDoorUID))
			
			PlayerCache(playerid)(pPackage) = true
			PlayerCache(playerid)(pPackageUID) = package_uid
			
			DisablePlayerCheckpoint(playerid)
			SetPlayerCheckpoint(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 2.0)

			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wziąłeś paczkę, dostarcz ją w wyznaczone miejsce.\nKiedy znajdziesz się w wyznaczonym miejscu użyj komendy /paczka., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_JOB)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					ShowPlayerDialog(playerid, D_SELECT_COURIER, DIALOG_STYLE_MSGBOX, Praca kuriera, Praca kuriera polega na rozwożeniu paczek do poszczególnych\ninstytucji. Za każdą paczkę otrzymasz odpowiednią sumę gotówki.\n\nKurier otrzymuje dostęp do specjalnej komendy,\ndzięki której może odebrać paczkę z hurtowni i przewieźć ją do\nmagazynu określonej instytucji.\n\nCzy jesteś pewien że chcesz podjąć się pracy kuriera?, Tak, Nie)
				)
				case 1:
				(
					ShowPlayerDialog(playerid, D_SELECT_FISHER, DIALOG_STYLE_MSGBOX, Praca rybaka, Praca rybaka polega na łowieniu ryb, które później można\nsprzedać za określoną cenę, bądź po prostu należycie zjeść.\n\nJednak trzeba pamiętać, że do łowienia ryb\npotrzebna będzie wędka, którą możesz zakupić\nw jednym ze sklepów całodobowych.\n\nCzy jesteś pewien że chcesz podjąć się pracy rybaka?, Tak, Nie)
				)
				/*case 2:
				(
					ShowPlayerDialog(playerid, D_SELECT_MECHANIC, DIALOG_STYLE_MSGBOX, Praca mechanika, Praca mechanika polega na naprawianiu, lakierowaniu, bądź tankowaniu\npojazdów. Za każdą zaoferowaną usługę zarabiasz konkretny procent.\n\nJest to praca dla miłośników motoryzacji, aby móc przelakierować\nkomuś pojazd, potrzebował będziesz do tego lakieru, który zakupić możesz w jakimś warsztacie.\n\nCzy jesteś pewien że chcesz podjąć się pracy mechanika?, Tak, Nie)
				)*/
				case 2:
				(
					ShowPlayerDialog(playerid, D_SELECT_SWEEPER, DIALOG_STYLE_MSGBOX, Praca sprzątacza, Praca sprzątacza polega na przemieszaniu się specjalnym pojazdem w celu czyszczenia\nulic Los Santos. Za każdy kurs zarabiasz wypłatę ustaloną wcześniej przez urząd miasta,\n który sponsoruje projekt.\n\nCzy jesteś pewien że chcesz podjąć się pracy sprzątacza ulic?, Tak, Nie)
				)
				/*case 3:
				(
					ShowPlayerDialog(playerid, D_SELECT_HOTDOG, DIALOG_STYLE_MSGBOX, Praca sprzedawcy hotdogów, Praca sprzedawcy hotdogów umożliwia Ci handlowanie hotdogami w budkach rozmieszczonych na mieście.\n\nCzy jesteś pewien że chcesz podjąć się pracy sprzątacza ulic?, Tak, Nie)
				)*/
				/*case 4:
				(
					ShowPlayerDialog(playerid, D_SELECT_PRESSER, DIALOG_STYLE_MSGBOX, Praca roznosiciela gazet, Praca polega na roznoszeniu gazet do pojemników porozstawianych w całym mieście. \n\nCzy chcesz podjąć się tej pracy?, Tak, Nie)
				)*/
				/*case 5:
				(
					ShowPlayerDialog(playerid, D_SELECT_SCOURER, DIALOG_STYLE_MSGBOX, Praca czyściciela tagów, Praca polega na usuwaniu tagów ze ścian, automatycznie zostanie Ci wręczona farba, dzięki której to zrobisz. \n\nCzy chcesz podjąć się tej pracy?, Tak, Nie)
				)*/
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_COURIER)
	(
		if(response)
		(
			PlayerCache(playerid)(pJob) = JOB_COURIER
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przyjałeś pracę kuriera.\n\nPracę możesz zacząć od zaraz, skorzystaj z\nkomendy /pomoc w celu ujrzenia nowych opcji., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_FISHER)
	(
		if(response)
		(
			PlayerCache(playerid)(pJob) = JOB_FISHER
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przyjąłeś pracę rybaka.\n\nPracę możesz zacząć od zaraz, skorzystaj z\nkomendy /pomoc w celu ujrzenia nowych opcji., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_MECHANIC)
	(
		if(response)
		(
	 		PlayerCache(playerid)(pJob) = JOB_MECHANIC
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przyjąłeś pracę mechanika.\n\nPracę możesz zacząć od zaraz, skorzystaj z\nkomendy /pomoc w celu ujrzenia nowych opcji., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_SWEEPER)
	(
		if(response)
		(
	 		PlayerCache(playerid)(pJob) = JOB_SWEEPER
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przyjąłeś pracę sprzątacza ulic.\n\nPracę możesz zacząć od zaraz, skorzystaj z\nkomendy /pomoc w celu ujrzenia nowych opcji., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_HOTDOG)
	(
		if(response)
		(
	 		PlayerCache(playerid)(pJob) = JOB_HOTDOG
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przyjąłeś pracę sprzedawcy hotdogów.\n\nPracę możesz zacząć od zaraz, skorzystaj z\nkomendy /pomoc w celu ujrzenia nowych opcji., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_PRESSER)
	(
		if(response)
		(
			PlayerCache(playerid)(pJob) = JOB_PRESSER
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przyjąłeś pracę dorywczą roznosiciela gazet., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_REMOVE_ITEM_BAG)
	(
		if(response)
		(
			if(!strval(inputtext))
			(
				return 1
			)		
			
			item_uid = strval(inputtext)
			
			if(GetItemWeightByUID(item_uid) ) GetPlayerEqSpace(playerid))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie masz wystarczająco miejsca w swoim ekwipunku aby wyciągnąć ten przedmiot., OK, )
				return 1
			)
			
			mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_PLAYER, PlayerCache(playerid)(pUID), item_uid)
			
			LoadItem(item_uid)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przedmiot został wyjęty.\nPojawił się on w Twoim ekwipunku., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_PUT_ITEM_BAG)
	(
		if(response)
		(
			itemid = PlayerCache(playerid)(pManageItem), item_uid = strval(inputtext),
				bagid = GetItemID(item_uid)
			
			if(GetBagEqSpace(bagid) ( ItemInfo(itemid)(iWeight))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, W tej torbie nie ma wystarczająco miejsca aby włożyć ten przedmiot., OK, )
				return 1	
			)
			
			mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_BAG, item_uid, ItemInfo(itemid)(iUID))
			
			ItemInfo(itemid)(iUID) = 0

			ItemInfo(itemid)(iValue1) = 0
			ItemInfo(itemid)(iValue2) = 0

			ItemInfo(itemid)(iType) = 0

			ItemInfo(itemid)(iPlace) = 0
			ItemInfo(itemid)(iOwner) = 0
			
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iChecked) = false
			
			Itter_Remove(Items, itemid)
			PlayerCache(playerid)(pManageItem) = 0
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przedmiot został włożony.\nAby wyjąć, użyj przedmiotu, do którego go włożyłeś., OK, )
			return 1
		)
		else
		(
			PlayerCache(playerid)(pManageItem) = 0
			return 1
		)
	)
	if(dialogid == D_MANAGE_VEH)
	(
		if(response)
		(
			vehid = GetPlayerVehicleID(playerid)
			switch(listitem)
			(
				case 0:
				(
					if(GetVehicleBonnetStatus(vehid) == 1)
					(
			   			ChangeVehicleBonnetStatus(vehid, false)
						GameTextForPlayer(playerid, ~w~Maska ~r~zamknieta, 5000, 3)
					)
					else
					(
				 		ChangeVehicleBonnetStatus(vehid, true)
						GameTextForPlayer(playerid, ~w~Maska ~g~otwarta, 5000, 3)
					)
				)
				case 1:
				(
			 		if(GetVehicleBootStatus(vehid) == 1)
					(
			  			ChangeVehicleBootStatus(vehid, false)
						GameTextForPlayer(playerid, ~w~Bagaznik ~r~zamkniety, 5000, 3)
					)
					else
					(
				 		ChangeVehicleBootStatus(vehid, true)
						GameTextForPlayer(playerid, ~w~Bagaznik ~g~otwarty, 5000, 3)
					)
				)
				case 2:
				(
		  			if(GetVehicleLightsStatus(vehid) == 1)
			 		(
						ChangeVehicleLightsStatus(vehid, false)
						GameTextForPlayer(playerid, ~w~Swiatla ~r~wylaczone, 5000, 3)
			   		)
					else
					(
				 		ChangeVehicleLightsStatus(vehid, true)
						GameTextForPlayer(playerid, ~w~Swiatla ~g~wlaczone, 5000, 3)
					)
				)
				case 3:
				(
					if(!CarInfo(vehid)(cRegister))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ten pojazd nie został zarejestrowany w urzędzie miasta., OK, )
						return 1
					)
					if(!PlayerCache(playerid)(pPremium))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ta funkcja jest dostępna tylko dla graczy posiadających aktywne konto premium., OK, )
						return 1
					)
				 	ShowPlayerDialog(playerid, D_EDIT_REGISTER, DIALOG_STYLE_INPUT, Własna rejestracja, Wprowadź poniżej treść własnej rejestracji.\nNapis na rejestracji zostanie zmieniony zgodnie z podana treścią.\n\nIlość znaków w rejestracji nie może przekroczyć 12., Zmień, Anuluj)
				)
				case 4:
				(
					if(!(CarInfo(vehid)(cAccess) & VEH_ACCESS_RADIO))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, W tym pojeździe nie zostało zamontowane CB radio., OK, )
						return 1
					)
					ShowPlayerDialog(playerid, D_RADIO_OPTIONS, DIALOG_STYLE_LIST, CB radio, 1. Ustaw kanał\n2. Wykup kanał na własność\n3. Ustaw hasło dla kanału\n4. Definitywnie usuń kanał\n5. Przypisz kanał pod grupę, Wybierz, Anuluj)
				)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ALARM_NUMBER)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					PlayerCache(playerid)(pAlarmCall) = 955
					ShowPlayerDialog(playerid, D_ALARM_CALL, DIALOG_STYLE_INPUT, Los Santos Police Department, Witam, z tej strony dyspozytor Los Santos Police Department, co się stało?\nProszę szczegółowo opisać sytuacje oraz podać miejsce położenia., Dalej, Anuluj)
				)
				case 1:
				(
					PlayerCache(playerid)(pAlarmCall) = 961
					ShowPlayerDialog(playerid, D_ALARM_CALL, DIALOG_STYLE_INPUT, Los Santos Emergency Medical Service, Witam, z tej strony dyspozytor Los Santos Medical Center, co się stało?\nProszę szczegółowo opisać sytuacje oraz podać miejsce położenia., Dalej, Anuluj)
				)
				case 2:
				(
					PlayerCache(playerid)(pAlarmCall) = 981
					ShowPlayerDialog(playerid, D_ALARM_CALL, DIALOG_STYLE_INPUT, Los Santos Fire Department, Witam, z tej strony dyspozytor Los Santos Fire Department, co się stało?\nProszę szczegółowo opisać sytuacje oraz podać miejsce położenia., Dalej, Anuluj)
				)
				case 3:
				(
					//mati - zmienić
					PlayerCache(playerid)(pAlarmCall) = 555
					ShowPlayerDialog(playerid, D_ALARM_CALL, DIALOG_STYLE_INPUT, Department Of Sanitation Electricity, Witam, z tej strony dyspozytor Department Of Sanitation Electricity, co się stało?\nProszę szczegółowo opisać sytuacje oraz podać miejsce położenia., Dalej, Anuluj)
				)
				case 4:
				(
					// fbi
					PlayerCache(playerid)(pAlarmCall) = 556
					ShowPlayerDialog(playerid, D_ALARM_CALL, DIALOG_STYLE_INPUT, Federal Bureau of Investigation, Witam, z tej strony dyspozytor Federal Bureau of Investigation, co się stało?\nProszę szczegółowo opisać sytuacje oraz podać miejsce położenia., Dalej, Anuluj)
				)
			)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			PlayerCache(playerid)(pAlarmCall) = INVALID_PLAYER_ID

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_ALARM_CALL)
	(
		if(response)
		(
			alarm_number = PlayerCache(playerid)(pAlarmCall), string(256), group_id_fix, counter = 0
			if(alarm_number == 556)
			(
				//FBI
				format(string, sizeof(string), Zgłaszający: %d, treść: %s, PlayerCache(playerid)(pSerivceNumberAs), inputtext)
				foreach(Player,i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pGroupDuty))
						(
							group_id_fix = GetPlayerDutyGroupID(i)
							if(GroupData(group_id_fix)(gType) == GROUP_FBI)
							(
								counter++
								SendClientMessage(i, COLOR_GREEN, Centrala: Do wszystkich jednostek, otrzymaliśmy zgłoszenie:)
								SendClientMessage(i, COLOR_GREEN, string)
							)
						)
					)
				)

			)
			if(alarm_number == 555)
			(
				//Department Of Sanitation Electricity na skrypcie CGH
				format(string, sizeof(string), Zgłaszający: %d, treść: %s, PlayerCache(playerid)(pSerivceNumberAs), inputtext)
				foreach(Player,i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pGroupDuty))
						(
							group_id_fix = GetPlayerDutyGroupID(i)
							if(GroupData(group_id_fix)(gType) == GROUP_MEDICAL)
							(
								counter++
								SendClientMessage(i, COLOR_GREEN, Centrala: Do wszystkich jednostek, otrzymaliśmy zgłoszenie:)
								SendClientMessage(i, COLOR_GREEN, string)
							)
						)
					)
				)
			)
			if(alarm_number == 955)
			(
				format(string, sizeof(string), Zgłaszający: %d, treść: %s, PlayerCache(playerid)(pSerivceNumberAs), inputtext)
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pGroupDuty))
						(
							group_id_fix = GetPlayerDutyGroupID(i)
							if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
							(
								counter++
								SendClientMessage(i, COLOR_GREEN, Centrala: Do wszystkich jednostek, otrzymaliśmy zgłoszenie:)
								SendClientMessage(i, COLOR_GREEN, string)
							)
						)
					)
				)
			)
			else if(alarm_number == 961)
			(
				format(string, sizeof(string), Zgłaszający: %d, treść: %s, PlayerCache(playerid)(pSerivceNumberAs), inputtext)
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pGroupDuty))
						(
							group_id_fix = GetPlayerDutyGroupID(i)
							if(GroupData(group_id_fix)(gType) == GROUP_MEDICAL || GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
							(
								counter++
								SendClientMessage(i, COLOR_GREEN, Centrala: Do wszystkich jednostek, otrzymaliśmy zgłoszenie:)
								SendClientMessage(i, COLOR_GREEN, string)
							)
						)
					)
				)
			)
			else if(alarm_number == 981)
			(
				format(string, sizeof(string), Zgłaszający: %d, treść: %s, PlayerCache(playerid)(pSerivceNumberAs), inputtext)
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pGroupDuty))
						(
							group_id_fix = GetPlayerDutyGroupID(i)
							if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
							(
								counter++
								SendClientMessage(i, COLOR_GREEN, Centrala: Do wszystkich jednostek, otrzymaliśmy zgłoszenie:)
								SendClientMessage(i, COLOR_GREEN, string)
							)
						)
					)
				)
			)
			format(string, sizeof(string), %s (telefon): %s,  PlayerName(playerid), inputtext)
		  	ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)

		  	format(string, sizeof(string), )) %d graczy na sluzbie otrzymalo Twoje zgloszenie., counter)
		  	SendClientMessage(playerid, COLOR_INFO, string)

   			MainPlayerTable(playerid) = 0
			PlayerCache(playerid)(pAlarmCall) = INVALID_PLAYER_ID

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
		else
		(
   			MainPlayerTable(playerid) = 0
			PlayerCache(playerid)(pAlarmCall) = INVALID_PLAYER_ID

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_SALON_OFFER_CAT)
	(
		if(response)
		(
			data(32), veh_category = strval(inputtext), list_vehicles(1024),
				salonveh_model, salonveh_price, salonveh_premium, giveplayer_id = MainPlayerTable(playerid)

			mysql_query_format(SELECT salonveh_model, salonveh_price, salonveh_premium FROM hrp_salonveh WHERE salonveh_cat = %d, veh_category)

			mysql_store_result()
			while(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)ddd, salonveh_model, salonveh_price, salonveh_premium)
				if(PlayerCache(giveplayer_id)(pPremium))
				(
					if(salonveh_premium == 1)
					(
						format(list_vehicles, sizeof(list_vehicles), %s\n$%d\t%s, list_vehicles, salonveh_price, VehicleData(salonveh_model - 400)(vName))	
					)
					else
					(
						format(list_vehicles, sizeof(list_vehicles), %s\n$%d\t%s, list_vehicles, salonveh_price, VehicleData(salonveh_model - 400)(vName))	
					)
				)
				else
				(
					if(salonveh_premium != 1)
					(
						format(list_vehicles, sizeof(list_vehicles), %s\n$%d\t%s, list_vehicles, salonveh_price, VehicleData(salonveh_model - 400)(vName))
					)
				)
			)
			mysql_free_result()
			if(strlen(list_vehicles))
			(
				ShowPlayerDialog(playerid, D_SALON_OFFER_VEH, DIALOG_STYLE_LIST, Oferuj pojazd, list_vehicles, Oferuj, Wróć)
			)
			else
			(
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~Brak pojazdow, 3000, 3)
				ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategorię, 1. Jednoślady\n2. Trzydrzwiowe\n3. Pięciodrzwiowe\n4. Furgonetki i ciężarówki\n5.Sportowe\n6. Lowridery \n7  Pickupy\n8  Latające\n9  Pływające\n10  Pozostałe , Wybierz, Anuluj)
				//ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategorię, 1. Jednoślady\n2. Trzydrzwiowe\n3. Pięciodrzwiowe\n4. Furgonetki i ciężarówki\n5. Pozostałe, Wybierz, Anuluj)
			)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_SALON_OFFER_VEH)
	(
		if(response)
		(
			salonveh_price, salonveh_name(32), giveplayer_id = MainPlayerTable(playerid)
			sscanf(inputtext, $ds(32), salonveh_price, salonveh_name)
			
			bool:has_house = false
			foreach(Doors, doorid)
			(
				if(DoorData(doorid)(dUID))
				(
					if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) == PlayerCache(giveplayer_id)(pUID))
					(
						has_house = true
						break
					)
				)
			)
			
			// Nowe komisy, więc zwiększamy ceny
			better_price = salonveh_price + floatround(salonveh_price * 0.10)

			if(has_house)
			(
				//OnPlayerSendOffer(playerid, giveplayer_id, OFFER_SALON, salonveh_name, GetVehicleModelByName(salonveh_name), salonveh_price)
				OnPlayerSendOffer(playerid, giveplayer_id, OFFER_SALON, salonveh_name, GetVehicleModelByName(salonveh_name), better_price)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ten gracz nie posiada jeszcze domu w związku z czym nie może kupić pojazdu., OK, )
			)

			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategorię, 1. Jednoślady\n2. Trzydrzwiowe\n3. Pięciodrzwiowe\n4. Furgonetki i ciężarówki\n5.Sportowe\n6. Lowridery \n7  Pickupy\n8  Latające\n9  Pływające\n10  Pozostałe , Wybierz, Anuluj)
			//ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategorię, 1. Jednoślady\n2. Trzydrzwiowe\n3. Pięciodrzwiowe\n4. Furgonetki i ciężarówki\n5. Pozostałe, Wybierz, Anuluj)
			return 1
		)
	)
	if(dialogid == D_BLOCK_WHEEL)
	(
		if(response)
		(
			price = strval(inputtext), vehid = MainPlayerTable(playerid), string(256)
			if(strlen(inputtext) ) 6 || price (= 0 || price ) 25000)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			CarInfo(vehid)(cWheelBlock) = price
			
			CarInfo(vehid)(cWorldID) = GetVehicleVirtualWorld(vehid)
			CarInfo(vehid)(cInteriorID) = GetPlayerInterior(playerid)
			
			GetVehiclePos(vehid, CarInfo(vehid)(cPosX), CarInfo(vehid)(cPosY), CarInfo(vehid)(cPosZ))
			GetVehiclePos(vehid, CarInfo(vehid)(cEPosX), CarInfo(vehid)(cEPosY), CarInfo(vehid)(cEPosZ))
			GetVehicleZAngle(vehid, CarInfo(vehid)(cPosA))
			
			SaveVehicle(vehid, SAVE_VEH_POS | SAVE_VEH_ACCESS)
			
			MainPlayerTable(playerid) = 0
			
			format(string, sizeof(string), Blokada na koło została założona.\n\nZablokowany pojazd: %s\nKoszt zdjęcia blokady: $%d\n\nPojazd został automatycznie zaparkowany w tym miejscu., CarInfo(vehid)(cName), price)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_TAXI_CALL)
	(
		if(response)
		(
			string(256), group_id_fix = PlayerCache(playerid)(pAlarmCall)
			format(string, sizeof(string), Wzywający: %d, treść: %s, PlayerCache(playerid)(pSerivceNumberAs), inputtext)

			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(PlayerCache(i)(pGroupDuty) == GroupData(group_id_fix)(gUID))
					(
						SendClientMessage(i, COLOR_GREEN, Centrala: Do wszystkich jednostek, otrzymaliśmy wezwanie:)
 						SendClientMessage(i, COLOR_GREEN, string)
					)
				)
			)
			format(string, sizeof(string), %s (telefon): %s,  PlayerName(playerid), inputtext)
		  	ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)

   			MainPlayerTable(playerid) = 0
			PlayerCache(playerid)(pAlarmCall) = INVALID_PLAYER_ID

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)

			SendClientMessage(playerid, COLOR_YELLOW, Sekretarka: Zgłoszenie zostało przyjęte do realizacji, już wysyłamy tam jednostkę.)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			PlayerCache(playerid)(pAlarmCall) = INVALID_PLAYER_ID

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_SN_CALL)
	(
		if(response)
		(
  			string(256), header(128), text(256)
			format(header, sizeof(header), Nowe zgłoszenie od numeru %d (%s):, PlayerCache(playerid)(pSerivceNumberAs), PlayerName(playerid))
			format(text, sizeof(text), Treść zgłoszenia: %s, inputtext)

			group_id_fix
			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(PlayerCache(i)(pGroupDuty))
					(
						group_id_fix = GetPlayerDutyGroupID(i)
						if(GroupData(group_id_fix)(gType) == GROUP_NEWS)
						(
	   						SendClientMessage(i, COLOR_GREEN, header)
	   						SendClientMessage(i, COLOR_GREEN, text)
						)
					)
				)
			)
			
			format(string, sizeof(string), %s (telefon): %s,  PlayerName(playerid), inputtext)
		  	ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)

   			MainPlayerTable(playerid) = 0
			PlayerCache(playerid)(pAlarmCall) = INVALID_PLAYER_ID

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)

			SendClientMessage(playerid, COLOR_YELLOW, Sekretarka: Dziękujemy za wysłane zgłoszenie, z pewnością będzie ono przydatne!)
			return 1
		)
		else
		(
   			MainPlayerTable(playerid) = 0
			PlayerCache(playerid)(pAlarmCall) = INVALID_PLAYER_ID

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_PRODUCT_SELECT)
	(
		if(response)
		(
			product_uid = strval(inputtext), product_id = GetProductID(product_uid), string(128)
			
			format(string, sizeof(string), %s (%d, %d) %d szt., ProductInfo(product_id)(pName), ProductInfo(product_id)(pValue1), ProductInfo(product_id)(pValue2), ProductInfo(product_id)(pNumber))
			ShowPlayerDialog(playerid, D_PRODUCT_OPTION, DIALOG_STYLE_LIST, string, 1. Wyjmij produkt\n2. Zmień cenę\n3. Usuń z magazynu, Wybierz, Anuluj)
			
			MainPlayerTable(playerid) = product_id
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_PRODUCT_GETNUM)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				out_num = strval(inputtext), product_id = MainPlayerTable(playerid), string(256)
				if(out_num ) 0)
				(
					if(ProductInfo(product_id)(pNumber) )= out_num)
					(
						ProductInfo(product_id)(pNumber) -= out_num
						if(ProductInfo(product_id)(pType) == ITEM_DRUG)
						(
						   	CreatePlayerItem(playerid, ProductInfo(product_id)(pName), ProductInfo(product_id)(pType), ProductInfo(product_id)(pValue1), ProductInfo(product_id)(pValue2) * out_num)
	   						format(string, sizeof(string), Wyjąłeś produkty z magazynu.\nProdukty pojawiły się w Twoim ekwipunku.)
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
						)
						else
						(
							for(i = 0 i ( out_num i++)
							(
								CreatePlayerItem(playerid, ProductInfo(product_id)(pName), ProductInfo(product_id)(pType), ProductInfo(product_id)(pValue1), ProductInfo(product_id)(pValue2))
							)
	   						format(string, sizeof(string), Wyjąłeś produkt z magazynu.\nProdukt pojawił się w Twoim ekwipunku.)
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
						)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie posiadasz tyle produktów., OK, )
					)

					if(ProductInfo(product_id)(pNumber) ( 1)
					(
						DeleteProduct(product_id)
					)
					else
					(
						SaveProduct(product_id, SAVE_PRODUCT_VALUES)
					)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Podana liczba musi być pozytywna., OK, )
				)
			)
			else
			(
				return 1
			)
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_PRODUCT_OPTION)
	(
		if(response)
		(
			product_id = MainPlayerTable(playerid), string(256)
			switch(listitem)
			(
				case 0:
				(
					if(ProductInfo(product_id)(pNumber) ) 1)
					(
						format(string, sizeof(string), Wpisz liczbę produktów do wyciągnięcia. (max. %d), ProductInfo(product_id)(pNumber))
						ShowPlayerDialog(playerid, D_PRODUCT_GETNUM, DIALOG_STYLE_INPUT, Wyjmij produkt, string, Wyciągnij, Anuluj)
					)
					else
					(
					   	CreatePlayerItem(playerid, ProductInfo(product_id)(pName), ProductInfo(product_id)(pType), ProductInfo(product_id)(pValue1), ProductInfo(product_id)(pValue2))

						ProductInfo(product_id)(pNumber) --
						DeleteProduct(product_id)
					
						format(string, sizeof(string), Wyjąłeś produkt z magazynu.\nNazwa produktu: %s (%d, %d)\n\nProdukt pojawił się w Twoim ekwipunku., ProductInfo(product_id)(pName), ProductInfo(product_id)(pValue1), ProductInfo(product_id)(pValue2))
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
					)
				)
				case 1:
				(
					format(string, sizeof(string), Wprowadź nową cenę, która będzie pobierana za kupno produktu.\n\nWybrałeś produkt: %s\nCena produktu: $%d, ProductInfo(product_id)(pName), ProductInfo(product_id)(pPrice))
					ShowPlayerDialog(playerid, D_PRODUCT_COSTS, DIALOG_STYLE_INPUT, Zmień cenę produktu, string, Zmień, Anuluj)
				)
				case 2:
				(
					format(string, sizeof(string), Czy jesteś pewien, że chcesz usunąć produkt?\n\nNazwa produktu: %s\nUID: %d, ProductInfo(product_id)(pName), ProductInfo(product_id)(pUID))
					ShowPlayerDialog(playerid, D_PRODUCT_DELETE, DIALOG_STYLE_MSGBOX, Usuń produkt z magazynu, string, Usuń, Anuluj)
				)
			)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_PRODUCT_COSTS)
	(
		if(response)
		(
			price = strval(inputtext), product_id = MainPlayerTable(playerid), string(128)
			if(price ( 0 || strlen(inputtext) ) 6)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			ProductInfo(product_id)(pPrice) = price
			SaveProduct(product_id, SAVE_PRODUCT_VALUES)
			
			format(string, sizeof(string), Produkt o nazwie %s kosztuje teraz $%d., ProductInfo(product_id)(pName), ProductInfo(product_id)(pPrice))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_PRODUCT_DELETE)
	(
		if(response)
		(
			product_id = MainPlayerTable(playerid)
			DeleteProduct(product_id)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Produkt został całkowicie usunięty z magazynu., OK, )
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_SELECT_SKILL)
	(
		return 1
	)
	if(dialogid == D_SELECT_BUSSTOP)
	(
		if(response)
		(
	 		busstop_id = PlayerCache(playerid)(pBusStart), busstop_id2, busstop_name(32), string(256)
			sscanf(inputtext, ds(32), busstop_id2, busstop_name)

			Float:distance = floatround(floatsqroot((BusStopData(busstop_id)(bPosX) - BusStopData(busstop_id2)(bPosX)) * (BusStopData(busstop_id)(bPosX) - BusStopData(busstop_id2)(bPosX)) + (BusStopData(busstop_id)(bPosY) - BusStopData(busstop_id2)(bPosY)) * (BusStopData(busstop_id)(bPosY) - BusStopData(busstop_id2)(bPosY))))

			PlayerCache(playerid)(pBusTravel) = busstop_id2
			PlayerCache(playerid)(pBusTime) = floatround(distance, floatround_floor) / 35

			if(PlayerCache(playerid)(pGamePoints) ( 100)
			(
				PlayerCache(playerid)(pBusPrice) = 0
				format(string, sizeof(string), Przejazd: %s -) %s.\n\nCzas trwania jazdy: %ds\nKoszt przejazdu: $%d (mniej niż 100GS)\n\nCzy jesteś pewien że chcesz się tam udać?, BusStopData(busstop_id)(bName), BusStopData(busstop_id2)(bName), PlayerCache(playerid)(pBusTime), PlayerCache(playerid)(pBusPrice))
			)
			else
			(
				workers = 0
				foreach(Groups, group_id_fix)
				(
					if(GroupData(group_id_fix)(gUID))
					(
						if(GroupData(group_id_fix)(gType) == GROUP_TAXI)
						(
							foreach(Player, i)
							(
								if(Logged(i) && Spawned(i))
								(
									if(PlayerCache(i)(pGroupDuty) == GroupData(group_id_fix)(gUID))
									(
					 					workers ++
									)
								)
							)
						)
					)
				)
				if(workers)
				(
					PlayerCache(playerid)(pBusPrice) = floatround(distance, floatround_floor) / 25
				)
				else
				(
					PlayerCache(playerid)(pBusPrice) = floatround(distance, floatround_floor) / 75
				)
				format(string, sizeof(string), Przejazd: %s -) %s.\n\nCzas trwania jazdy: %ds\nKoszt przejazdu: $%d\n\nCzy jesteś pewien że chcesz się tam udać?, BusStopData(busstop_id)(bName), BusStopData(busstop_id2)(bName), PlayerCache(playerid)(pBusTime), PlayerCache(playerid)(pBusPrice))
			)

			ShowPlayerDialog(playerid, D_ACCEPT_TRAVEL, DIALOG_STYLE_MSGBOX, Przejazd autobusem, string, Jedź, Anuluj)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_ACCEPT_TRAVEL)
	(
		if(response)
		(
  			price = PlayerCache(playerid)(pBusPrice), busstop_id = PlayerCache(playerid)(pBusStart), busstop_id2 = PlayerCache(playerid)(pBusTravel)
			if(PlayerCache(playerid)(pCash) ( price)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiedniej ilości gotówki., OK, )
				return 1
			)
			hrp_GivePlayerMoney(playerid, -price)

			SetPlayerVirtualWorld(playerid, 5000 + playerid)
			//SetPlayerInterior(playerid, 1000 + playerid)

			//hrp_SetPlayerPos(playerid, 0, 0, 5)
			TogglePlayerControllable(playerid, 0)

			SetPlayerCameraPos(playerid, BusStopData(busstop_id)(bPosX), BusStopData(busstop_id)(bPosY), BusStopData(busstop_id)(bPosZ) + 50)
			SetPlayerCameraLookAt(playerid, BusStopData(busstop_id2)(bPosX), BusStopData(busstop_id2)(bPosY), BusStopData(busstop_id2)(bPosZ))

			InterpolateCameraPos(playerid, BusStopData(busstop_id)(bPosX), BusStopData(busstop_id)(bPosY), BusStopData(busstop_id)(bPosZ) + 50, BusStopData(busstop_id2)(bPosX), BusStopData(busstop_id2)(bPosY), BusStopData(busstop_id2)(bPosZ), PlayerCache(playerid)(pBusTime) * 1000, CAMERA_MOVE)

			PlayerPlaySound(playerid, 1076, 0.0, 0.0, 0.0)
			PlayerCache(playerid)(pBusRide) = true
			return 1
		)
		else
		(
   			PlayerCache(playerid)(pBusStart) = 0
			PlayerCache(playerid)(pBusTravel) = 0
			
			PlayerCache(playerid)(pBusTime) = 0
			PlayerCache(playerid)(pBusPrice) = 0
			return 1
		)
	)
	if(dialogid == D_SALON_PRICE_LIST)
	(
		if(response)
		(
			data(32), veh_category = strval(inputtext), list_vehicles(1024),
				salonveh_model, salonveh_price, salonveh_premium

			mysql_query_format(SELECT salonveh_model, salonveh_price, salonveh_premium FROM hrp_salonveh WHERE salonveh_cat = %d, veh_category)

			mysql_store_result()
			while(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)ddd, salonveh_model, salonveh_price, salonveh_premium)
				if(salonveh_premium == 1)
				(
					format(list_vehicles, sizeof(list_vehicles), %s\n$%d\t%s (premium), list_vehicles, salonveh_price, VehicleData(salonveh_model - 400)(vName))	
				)
				else
				(
					format(list_vehicles, sizeof(list_vehicles), %s\n$%d\t%s, list_vehicles, salonveh_price, VehicleData(salonveh_model - 400)(vName))	
				)
			)
			mysql_free_result()
			if(strlen(list_vehicles))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Cennik pojazdów, list_vehicles, OK, Zamknij)
			)
			else
			(
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~Brak pojazdow, 3000, 3)
				ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategorię, 1. Jednoślady\n2. Trzydrzwiowe\n3. Pięciodrzwiowe\n4. Furgonetki i ciężarówki\n5.Sportowe\n6. Lowridery \n7  Pickupy\n8  Latające\n9  Pływające\n10  Pozostałe , Wybierz, Anuluj)
				//ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategorię, 1. Jednoślady\n2. Trzydrzwiowe\n3. Pięciodrzwiowe\n4. Furgonetki i ciężarówki\n5. Pozostałe, Wybierz, Anuluj)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_INTRODUCTION)
	(
		if(response)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wprowadzenie (2/2), Możesz śmiało poruszać się po mieście, korzystając z przystanku autobusowego (/bus)\nbądź dzwoniąc po taksówkę na numer 777 (wymagany telefon).\n\nZatrudnij się w jakiejś instytucji, by zacząć zarabiać pieniądze na dom, samochód i inne ciekawe rzeczy,\nale nie rób tego stojąc pod urzędem, sam pochodź po mieście rozglądając się za ofertami pracy.\n\nMiłej gry, życzy ekipa SERVER_NAME!, OK, Zamknij)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ACTION_CRAFT)
	(
		if(response)
		(
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_DRUG_USE)
	(
		if(response)
		(
		
			item_uid = strval(inputtext), itemid = GetItemID(item_uid)
			if(ItemInfo(itemid)(iType) == ITEM_BONGOS)
			(
				ItemInfo(itemid)(iValue1) += 1
				mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wykorzystałeś 1g marihuany do użycia w bongosie.\nOd tej pory możesz już użyć bongosa., OK, )
			)
			else
			(
				ItemInfo(itemid)(iValue1) --
		   		if(ItemInfo(itemid)(iValue1) (= 0)
				(
					DeleteItem(ItemInfo(itemid)(iValue1))
				)
		  		else
		  		(
					mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
				)
			
				CreatePlayerItem(playerid, Joint, ITEM_JOINT, 0, 0)
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Skręciłeś Jointa z 1g marihuany.\nPrzedmiot znajdziesz w swoim ekwipunku., OK, )
			)
			itemid = MainPlayerTable(playerid)

			ItemInfo(itemid)(iValue2) --
			if(ItemInfo(itemid)(iValue2) (= 0)
			(
				DeleteItem(ItemInfo(itemid)(iUID))
				return 1
			)
   			new_name(24)

			format(new_name, sizeof(new_name), Marihuana - %d g, ItemInfo(itemid)(iValue2))
   			strmid(ItemInfo(itemid)(iName), new_name, 0, strlen(new_name), 24)
			
			mysql_query_format(UPDATE hrp_items SET item_name = %s, item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iName), ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TYPE_AMPHETAMINE_USE)
	(
		if(response)
		(
			itemid = MainPlayerTable(playerid), string(128), Float:health
			GetPlayerHealth(playerid, health)
			
			MainPlayerTable(playerid) = 0
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postać czuje się bardziej pobudzona.\n\nPrzez jakiś czas będziesz zadawać większe obrażenia., OK, )
			
			DeleteItem(ItemInfo(itemid)(iUID))
			
			PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
			PlayerCache(playerid)(pRageDrug) = DRUG_AMPHETAMINE
			
			switch(listitem)
			(
				//Palenie
				case 0:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_SMOKE
					PlayerCache(playerid)(pRageTime) = 900
					PlayerCache(playerid)(pRageDrunkLevel) = 3500
					PlayerCache(playerid)(pStrength) += 30.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 18.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 8.3
					)

					format(string, sizeof(string), * %s zażywa %s paląc., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
				//Wziewnie do nosa
				case 1:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_SNORT
					PlayerCache(playerid)(pRageTime) = 1200
					PlayerCache(playerid)(pRageDrunkLevel) = 3700
					PlayerCache(playerid)(pStrength) += 35.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 21.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 10.3
					)

					format(string, sizeof(string), * %s zażywa %s wciągając przez nos., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
				//Dożylnie
				case 2:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_INJECT
					PlayerCache(playerid)(pRageTime) = 1800
					PlayerCache(playerid)(pRageDrunkLevel) = 3200
					PlayerCache(playerid)(pStrength) += 19.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 14.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 12.3
					)

					format(string, sizeof(string), * %s zażywa %s dożylnie., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
			)
			PlayerCache(playerid)(pDrugLevel) += 200
			hrp_SetPlayerHealth(playerid, health + 10.0)
			PlayerCache(playerid)(pRage) = true
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TYPE_LSD_USE)
	(
		if(response)
		(
			itemid = MainPlayerTable(playerid), string(128), Float:health
			GetPlayerHealth(playerid, health)
			
			MainPlayerTable(playerid) = 0
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postać zaczyna czuć efekty działania narkotyku.\nInformacje o działaniu konkretnego narkotyku znajdziesz na naszym forum., OK, )
			
			DeleteItem(ItemInfo(itemid)(iUID))
			
			PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_GUMS
			PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
			PlayerCache(playerid)(pRageDrug) = DRUG_LSD

			switch(listitem)
			(
				//Papierek pod język
				case 0:
				(
					PlayerCache(playerid)(pRageTime) = 1800
					PlayerCache(playerid)(pRageDrunkLevel) = 2100

					format(string, sizeof(string), * %s zażywa %s poprzez papierek pod językiem., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
				//Roztwór
				case 1:
				(
					PlayerCache(playerid)(pRageTime) = 1600
					PlayerCache(playerid)(pRageDrunkLevel) = 2500

					format(string, sizeof(string), * %s zażywa %s poprzez roztwór., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
			)
			PlayerCache(playerid)(pDrugLevel) += 200			
			SetPlayerWeather(playerid, -66)
			PlayerCache(playerid)(pRage) = true
			return 1
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_TYPE_METAAMP_USE)
	(
		if(response)
		(
			itemid = MainPlayerTable(playerid), string(128), Float:health
			GetPlayerHealth(playerid, health)
			
			MainPlayerTable(playerid) = 0
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postać czuje się bardziej pobudzona.\n\nPrzez jakiś czas będziesz zadawać większe obrażenia., OK, )
			
			DeleteItem(ItemInfo(itemid)(iUID))
			
			PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
			PlayerCache(playerid)(pRageDrug) = DRUG_MDMA
			hrp_SetPlayerHealth(playerid, health + 30.0)

			switch(listitem)
			(
				//Palenie
				case 0:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_SMOKE
					PlayerCache(playerid)(pRageTime) = 1200
					PlayerCache(playerid)(pRageDrunkLevel) = 0
					PlayerCache(playerid)(pStrength) += 60.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 40.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 20.3
					)

					SetPlayerWeather(playerid, -66)
					
					format(string, sizeof(string), * %s zażywa %s paląc., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
				//Wziewanie do nosa
				case 1:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_SNORT
					PlayerCache(playerid)(pRageTime) = 1200
					PlayerCache(playerid)(pRageDrunkLevel) = 0
					PlayerCache(playerid)(pStrength) += 50.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 35.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 16.3
					)

					format(string, sizeof(string), * %s zażywa %s wziewając do nosa., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
				//Dożylnie
				case 2:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_INJECT
					PlayerCache(playerid)(pRageTime) = 1800
					PlayerCache(playerid)(pRageDrunkLevel) = 0
					PlayerCache(playerid)(pStrength) += 47.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 47.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 32.3
					)

					format(string, sizeof(string), * %s zażywa %s dożylnie., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
			)
			PlayerCache(playerid)(pDrugLevel) += 200
			hrp_SetPlayerHealth(playerid, health + 10.0)
			PlayerCache(playerid)(pRage) = true
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TYPE_HEROIN_USE)
	(
		if(response)
		(
			itemid = MainPlayerTable(playerid), string(128), Float:health
			GetPlayerHealth(playerid, health)
			
			MainPlayerTable(playerid) = 0
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postać zaczyna czuć efekty działania narkotyku.\nInformacje o działaniu konkretnego narkotyku znajdziesz na naszym forum., OK, )
			
			DeleteItem(ItemInfo(itemid)(iUID))
			
			PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
			PlayerCache(playerid)(pRageDrug) = DRUG_HEROIN

			switch(listitem)
			(
				// Wciąganie
				case 0:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_SNORT
					PlayerCache(playerid)(pRageTime) = 900
					PlayerCache(playerid)(pRageDrunkLevel) = 5100
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 18.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 13.3
					)

					format(string, sizeof(string), * %s zażywa %s wciągając., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
				//Palenie
				case 1:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_SMOKE
					PlayerCache(playerid)(pRageTime) = 1200
					PlayerCache(playerid)(pRageDrunkLevel) = 5500
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 28.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 8.3
					)

					format(string, sizeof(string), * %s zażywa %s paląc., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)					
				)
				//Dożylnie
				case 2:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_INJECT
					PlayerCache(playerid)(pRageTime) = 1800
					PlayerCache(playerid)(pRageDrunkLevel) = 8100
					
					hrp_SetPlayerHealth(playerid, health + 100.0)
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 35.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 13.3
					)

					format(string, sizeof(string), * %s zażywa %s dożylnie., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)									
				)
			)
			PlayerCache(playerid)(pDrugLevel) += 200
			PlayerCache(playerid)(pRage) = true
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_TYPE_COCAINE_USE)
	(
		if(response)
		(
			itemid = MainPlayerTable(playerid), string(128), Float:health
			GetPlayerHealth(playerid, health)
			
			MainPlayerTable(playerid) = 0
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postać czuje się bardziej pobudzona.\n\nPrzez jakiś czas będziesz zadawać większe obrażenia., OK, )
			
			DeleteItem(ItemInfo(itemid)(iUID))
			
			PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
			PlayerCache(playerid)(pRageDrug) = DRUG_COCAINE

			switch(listitem)
			(
				// Wcieranie w dziąsla
				case 0:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_GUMS
					PlayerCache(playerid)(pRageTime) = 900
					PlayerCache(playerid)(pRageDrunkLevel) = 3100
					PlayerCache(playerid)(pStrength) += 40.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 28.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 10.3
					)

					format(string, sizeof(string), * %s zażywa %s wcierając w dziąsła., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				)
				//Wziewanie do nosa
				case 1:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_SNORT
					PlayerCache(playerid)(pRageTime) = 1200
					PlayerCache(playerid)(pRageDrunkLevel) = 3500
					PlayerCache(playerid)(pStrength) += 30.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 22.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 8.3
					)

					format(string, sizeof(string), * %s zażywa %s wziewając do nosa., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)					
				)
				//Żucie
				case 2:
				(
					PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_GUMS
					PlayerCache(playerid)(pRageTime) = 1200
					PlayerCache(playerid)(pRageDrunkLevel) = 1500
					PlayerCache(playerid)(pStrength) += 15.0
					
					if(PlayerCache(playerid)(pDependence) ( 500)
					(
						PlayerCache(playerid)(pDependence) += 12.3
					)
					else
					(
						PlayerCache(playerid)(pDependence) += 4.3
					)

					format(string, sizeof(string), * %s zażywa %s żując., PlayerName(playerid), ItemInfo(itemid)(iName))
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)									
				)
			)
			PlayerCache(playerid)(pDrugLevel) += 200
			hrp_SetPlayerHealth(playerid, health + 50.0)
			PlayerCache(playerid)(pRage) = true
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_ASSIGN_VEH)
	(
		if(response)
		(
			group_slot = strval(inputtext) - 1, vehid = GetPlayerVehicleID(playerid), string(256)
			if(vehid == INVALID_VEHICLE_ID)
  			(
  				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w pojeździe, który chcesz przypisać., OK, )
   				return 1
			)
			if(group_slot ( 0)
			(
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Anulowano., 3000, 3)
				return 1
			)
			if(!IsPlayerPermissedGroup(playerid, PlayerGroup(playerid)(group_slot)(gUID), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień dla tej grupy., OK, )
				return 1
			)
			group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
			MainPlayerTable(playerid) = group_id_fix
			
			format(string, sizeof(string), Czy chcesz przypisać pojazd %s (SampID: %d, UID: %d) pod grupę %s (UID: %d)?, CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			ShowPlayerDialog(playerid, D_ASSIGN_VEH_ACCEPT, DIALOG_STYLE_MSGBOX, Pojazd » Przypisz pod grupę, string, Tak, Nie)
			return 1
		)
		else
		(
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Anulowano., 3000, 3)
			return 1
		)
	)
	if(dialogid == D_ASSIGN_VEH_ACCEPT)
	(
		if(response)
		(
			vehid = GetPlayerVehicleID(playerid), string(128)
	  		if(vehid == INVALID_VEHICLE_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znajdujesz się w pojeździe, który chcesz przypisać., OK, )
				return 1
			)
			group_id_fix = MainPlayerTable(playerid)
			
			CarInfo(vehid)(cOwnerType) = OWNER_GROUP
			CarInfo(vehid)(cOwner) = GroupData(group_id_fix)(gUID)

			SaveVehicle(vehid, SAVE_VEH_THINGS)
			PlayerCache(playerid)(pCarSpawned) --

			format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) został pomyślnie przypisany pod grupyę.\nPojazd przypisano dla grupy %s (UID: %d)., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

			hrp_VehicleActionLog(%s (UID: %d) przypisal pojazd %s (UID: %d) pod grupe %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_LIST_PLAYERS)
	(
		if(response)
		(
			clickedplayerid = strval(inputtext)
			OnPlayerClickPlayer(playerid, clickedplayerid, 0)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_SPAWN)
	(
		if(response)
		(
			spawn_name(12), string(64)
			strmid(spawn_name, inputtext, 0, strlen(inputtext), 12)
			
			if(!strcmp(spawn_name, Cywil, true)) 			PlayerCache(playerid)(pSpawnPlace) = SPAWN_NONE
			if(!strcmp(spawn_name, Hotel, true)) 			PlayerCache(playerid)(pSpawnPlace) = SPAWN_HOTEL
			if(!strcmp(spawn_name, Mieszkanie, true)) 	PlayerCache(playerid)(pSpawnPlace) = SPAWN_HOUSE
			if(!strcmp(spawn_name, Dom rodzinny, true)) 	PlayerCache(playerid)(pSpawnPlace) = SPAWN_FAMILYHOUSE
			
			format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~y~Spawn ~g~zmieniony ~y~- ~p~%s, spawn_name)
			GameTextForPlayer(playerid, string, 3000, 3)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RECORD_DISC)
	(
		if(response)
		(
			itemid = PlayerCache(playerid)(pManageItem), audio_url(256),
				audio_uid

			printf((debug) PlayerCache(playerid)(pManageItem) = %d, PlayerCache(playerid)(pManageItem))
			printf((debug) ItemInfo(itemid)(iUID) = %d, ItemInfo(itemid)(iUID))

			if(strfind(inputtext, http://, true))
			(
				ShowPlayerDialog(playerid, D_RECORD_DISC, DIALOG_STYLE_INPUT, Nagrywanie płyty, To jest czysta płyta, na której możesz nagrać dowolny kawałek.\nWklej w pole tekstowe poniżej link do muzyki, która ma być odtwarzana poprzez urządzenia.\n\nUpewnij się, że link jest poprawny w innym wypadku muzyka może nie być słyszalna.\n\nDługość linku nie może przekroczyć 64 znaków.\n\n(FF0000)* Link musi rozpoczynać się na \http://\., Nagraj, Anuluj)
				return 1
			)
			if(strlen(inputtext) (= 0)
			(
				ShowPlayerDialog(playerid, D_RECORD_DISC, DIALOG_STYLE_INPUT, Nagrywanie płyty, To jest czysta płyta, na której możesz nagrać dowolny kawałek.\nWklej w pole tekstowe poniżej link do muzyki, która ma być odtwarzana poprzez urządzenia.\n\nUpewnij się, że link jest poprawny w innym wypadku muzyka może nie być słyszalna.\n\nDługość linku nie może przekroczyć 64 znaków.\n\n(FF0000)* Te pole nie może być puste!, Nagraj, Anuluj)
				return 1
			)
			if(strlen(inputtext) ) 64)
			(
				ShowPlayerDialog(playerid, D_RECORD_DISC, DIALOG_STYLE_INPUT, Nagrywanie płyty, To jest czysta płyta, na której możesz nagrać dowolny kawałek.\nWklej w pole tekstowe poniżej link do muzyki, która ma być odtwarzana poprzez urządzenia.\n\nUpewnij się, że link jest poprawny w innym wypadku muzyka może nie być słyszalna.\n\nDługość linku nie może przekroczyć 64 znaków.\n\n(FF0000)* Link nie może przekroczyć 64 znaków!, Nagraj, Anuluj)
				return 1
			)
			mysql_real_escape_string(inputtext, audio_url)
			
			mysql_query_format(INSERT INTO hrp_audiourls (audio_url) VALUES (%s), audio_url)
			
			audio_uid = mysql_insert_id()
			
			ItemInfo(itemid)(iValue1) = audio_uid
			mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
			
			ShowPlayerDialog(playerid, D_RECORD_DISC_NAME, DIALOG_STYLE_INPUT, Nagrywanie płyty » Nazwa, Wprowadż w pole poniżej nazwę Twojej płyty, która będzie rozpoznawana w ekwipunku.\n\nNazwa nie może przekroczyć 12 znaków., Nagraj, Pomiń)
			return 1
		)
		else
		(
			PlayerCache(playerid)(pManageItem) = 0
			return 1
		)
	)
	if(dialogid == D_RECORD_DISC_NAME)
	(
		if(response)
		(
			itemid = PlayerCache(playerid)(pManageItem), string(128),
				item_name(32)
			
	  		if(strlen(inputtext) (= 0)
			(
				ShowPlayerDialog(playerid, D_RECORD_DISC_NAME, DIALOG_STYLE_INPUT, Nagrywanie płyty » Nazwa, Wprowadż w pole poniżej nazwę Twojej płyty, która będzie rozpoznawana w ekwipunku.\n\nNazwa nie może przekroczyć 12 znaków.\n\n(FF0000)* Te pole nie może być puste!, Nagraj, Pomiń)
				return 1
			)
			if(strlen(inputtext) )= 12)
			(
				ShowPlayerDialog(playerid, D_RECORD_DISC_NAME, DIALOG_STYLE_INPUT, Nagrywanie płyty » Nazwa, Wprowadż w pole poniżej nazwę Twojej płyty, która będzie rozpoznawana w ekwipunku.\n\nNazwa nie może przekroczyć 12 znaków.\n\n(FF0000)* Nazwa nie może przekroczyć więcej niż 12 znaków!, Nagraj, Pomiń)
				return 1
			)
			mysql_real_escape_string(inputtext, item_name)
			
			format(item_name, sizeof(item_name), (CD) %s, item_name)
			
			PlayerCache(playerid)(pManageItem) = 0
			strmid(ItemInfo(itemid)(iName), item_name, 0, strlen(item_name), 32)
			
			
			mysql_query_format(UPDATE hrp_items SET item_name = %s WHERE item_uid = %d LIMIT 1, item_name, ItemInfo(itemid)(iUID))
			
			format(string, sizeof(string), Płyta została pomyślnie nagrana.\nPłytę nazwałeś następująco: %s.\n\nPłyty tej możesz odsłuchać w discmanie albo w radiu w pojeździe., ItemInfo(itemid)(iName))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			return 1
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zmiana nazwy płyty została pominięta.\nNazwa nie została zmieniona., OK, )
			PlayerCache(playerid)(pManageItem) = 0
			return 1
		)
	)
	if(dialogid == D_INSERT_DISC)
	(
		if(response)
		(
			itemid = PlayerCache(playerid)(pManageItem), item_uid = strval(inputtext), itemid2 = GetItemID(item_uid), string(128)
			
			PlayerCache(playerid)(pManageItem) = 0
			ItemInfo(itemid2)(iValue1) = ItemInfo(itemid)(iValue1)

			mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid2)(iValue1), ItemInfo(itemid2)(iUID))
			
			if(PlayerCache(playerid)(pMusicPlayerUID) == ItemInfo(itemid2)(iUID) && ItemInfo(itemid2)(iUsed))
			(
				if(PlayerCache(playerid)(pAudioHandle))
				(
					//Audio_Stop(playerid, PlayerCache(playerid)(pAudioHandle))
					PlayerCache(playerid)(pAudioHandle) = 0
					StopAudioStreamForPlayer(playerid)
				)
				PlayerCache(playerid)(pMusicPlayerUID) = 0
				ItemInfo(itemid2)(iUsed) = 0
			)
			
			format(string, sizeof(string), * %s umieszcza płytę w odtwarzaczu., PlayerName(playerid))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)

			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Płyta została umieszczona w odtwarzaczu.\nUżyj odtwarzacza, by rozpocząć słuchanie muzyki., OK, )
			return 1
		)
		else
		(
			PlayerCache(playerid)(pManageItem) = 0
			return 1
		)
	)
	if(dialogid == D_REMOVE_ITEM_SAFE)
	(
		if(response)
		(
	 		if(!strval(inputtext))
			(
				return 1
			)
	 		item_uid = strval(inputtext)
			
			if(GetItemWeightByUID(item_uid) ) GetPlayerEqSpace(playerid))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie masz wystarczająco miejsca w swoim ekwipunku aby wyciągnąć ten przedmiot., OK, )
				return 1
			)
			
			mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_PLAYER, PlayerCache(playerid)(pUID), item_uid)

			LoadItem(item_uid)

			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przedmiot został wyjęty.\nPojawił się on w Twoim ekwipunku., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DIRECTORY_INFO)
	(
		if(response)
		(
			directory_uid = strval(inputtext)
			mysql_query_format(SELECT directory_date, directory_reason, directory_author, char_name, char_pdp FROM hrp_directory, hrp_characters WHERE directory_uid = 2 AND char_uid = directory_owner LIMIT 1, directory_uid)

			data(128), string(256),
				directory_date(24), directory_reason(32), directory_owner(24), directory_author(24), char_pdp
				
			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)s(24)s(32)s(24)s(24)d, directory_date, directory_reason, directory_owner, directory_author, char_pdp)
			)
			mysql_free_result()
			
			pos = strfind(directory_owner, _, true)
			if(pos != -1)	(	directory_owner(pos) =  	)
			
			format(string, sizeof(string), Identyfikator wpisu: %d\nWłaściciel: %s\nPunkty karne: %d\n\nAutor wpisu: %s\nTreść:\n\n%s, directory_uid, directory_owner, char_pdp, directory_author, directory_reason)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Szczegóły, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_EDIT_REGISTER)
	(
		if(response)
		(
			if(strlen(inputtext) ) 12)
			(
				ShowPlayerDialog(playerid, D_EDIT_REGISTER, DIALOG_STYLE_INPUT, Własna rejestracja, Wprowadź poniżej treść własnej rejestracji.\nNapis na rejestracji zostanie zmieniony zgodnie z podana treścią.\n\nIlość znaków w rejestracji nie może przekroczyć 12.\n\n(FF0000)* Podana treść nie może przekroczyć liczby 12 znaków, Zmień, Anuluj)
				return 1
			)
			if(!strfind(inputtext, LS, true))
			(
				ShowPlayerDialog(playerid, D_EDIT_REGISTER, DIALOG_STYLE_INPUT, Własna rejestracja, Wprowadź poniżej treść własnej rejestracji.\nNapis na rejestracji zostanie zmieniony zgodnie z podana treścią.\n\nIlość znaków w rejestracji nie może przekroczyć 12.\n\n(FF0000)* Nie możesz wpisać tej treści w rejestracji, Zmień, Anuluj)
				return 1
			)
			vehid = GetPlayerVehicleID(playerid), register_desc(32)

			strmid(register_desc, inputtext, 0, strlen(inputtext), 12)
		 	SetVehicleNumberPlate(vehid, register_desc)
		 	
		 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Treść rejestracji została pomyślnie zmodyfikowana.\nTablice powinny ulec zmianie, jeśli nie teraz, to po jakimś czasie., OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_CLOTH_OPTION)
	(
		if(response)
		(
			player_vw = GetPlayerVirtualWorld(playerid), door_id = GetDoorID(player_vw), shop_type = 0, group_id_fix = GetGroupID(DoorData(door_id)(dOwner))
			shop_type = GroupData(group_id_fix)(gValue1)
			
			if(shop_type == 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wystąpił niespodziewany błąd., OK, )
				return 1
			)
			
			PlayerCache(playerid)(pAccessShop) = shop_type
		
 			Float:PosX, Float:PosY, Float:PosZ
			GetPlayerPos(playerid, PosX, PosY, PosZ)

			GetXYInFrontOfPlayer(playerid, PosX, PosY, 3.0)
			SetPlayerCameraPos(playerid, PosX, PosY, PosZ + 0.30)

			GetPlayerPos(playerid, PosX, PosY, PosZ)
			hrp_TogglePlayerControllable(playerid, false)

			switch(listitem)
			(
				case 0:
				(
					PlayerCache(playerid)(pClothChanging) = true
					PlayerCache(playerid)(pClothID) = 0

					TextDrawSetString(Text:TextDrawMainInfo(playerid), Aby ~b~poruszac ~w~sie pomiedzy skinami ~r~uzywaj ~w~klawiszy ~(~ oraz ~)~~n~~n~~y~~k~~PED_JUMPING~ ~w~- anuluje wybor~n~~y~~k~~VEHICLE_ENTER_EXIT~ ~w~- zakup ubrania)
					TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
					
					SetPlayerCameraLookAt(playerid, PosX, PosY, PosZ)
				)
				case 1:
				(
					PlayerCache(playerid)(pAccessChanging) = true
					PlayerCache(playerid)(pAccessID) = 0
					
					//TextDrawSetString(Text:TextDrawMainInfo(playerid), Aby ~b~poruszac ~w~sie pomiedzy akcesoriami ~r~uzywaj ~w~strzalek~n~~n~~y~~k~~PED_JUMPING~ ~w~- anuluje wybor~n~~y~~k~~VEHICLE_ENTER_EXIT~ ~w~- zakup akcesoria~n~~n~~y~~k~~SNEAK_ABOUT~ + STRZALKA ~w~- pozycjonowanie~n~~y~~k~~PED_SPRINT~ + STRZALKA ~w~- skalowanie)
					//TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
					
					string(256)
					sendClientPoop(playerid, » Używaj strzałek do poruszania się między akcesoriami.)
					
					format(string, sizeof(string), » ~k~~PED_JUMPING~ aby anulować i ~k~~VEHICLE_ENTER_EXIT~ by kupić.)
					sendClientPoop(playerid, string)
					
					SetPlayerCameraLookAt(playerid, PosX, PosY, PosZ + 0.5)
				)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ACCESS_APPLY)
	(
		if(response)
		(
			itemid = PlayerCache(playerid)(pManageItem)
			
			ItemInfo(itemid)(iUsed) = 1
			PlayerCache(playerid)(pManageItem) = 0

			if(!strfind(ItemInfo(itemid)(iName), (B), true))
			(
				PlayerCache(playerid)(pMaskUID) = ItemInfo(itemid)(iUID)
			)
			
			RemovePlayerAttachedObject(playerid, SLOT_ACCESS_ONE)
			RemovePlayerAttachedObject(playerid, SLOT_ACCESS_TWO)
			
			// Konto premium
			if(PlayerCache(playerid)(pPremium))
			(
				RemovePlayerAttachedObject(playerid, SLOT_ACCESS_THREE)
			)
			if(PlayerCache(playerid)(pAASlot))
			(
				RemovePlayerAttachedObject(playerid, SLOT_ACCESS_FOUR)
			)

			mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
			LoadPlayerAccess(playerid)
			return 1
		)
		else
		(
			if(IsPlayerInAnyVehicle(playerid))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Nie możesz edytować akcesoria podczas, gdy siedzisz w pojeździe., OK, )
				return 1
			)
			if(PlayerCache(playerid)(pBlock) & BLOCK_OBJ)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Możliwość edycji akcesorii została dla Ciebie zablokowana., OK, )
				return 1
			)
  			//Float:PosX, Float:PosY, Float:PosZ
			//GetPlayerPos(playerid, PosX, PosY, PosZ)

			//GetXYInFrontOfPlayer(playerid, PosX, PosY, 3.0)
			//SetPlayerCameraPos(playerid, PosX, PosY, PosZ + 0.30)

			//GetPlayerPos(playerid, PosX, PosY, PosZ)
			//SetPlayerCameraLookAt(playerid, PosX, PosY, PosZ)

			//hrp_TogglePlayerControllable(playerid, false)
			PlayerCache(playerid)(pAccessEditing) = true
			
			data(256), itemid = PlayerCache(playerid)(pManageItem)
			mysql_query_format(SELECT * FROM hrp_access WHERE access_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1))
			
			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)dddfffffffff, PlayerAttach(playerid)(aUID), PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
			)
			mysql_free_result()

			EditAttachedObject(playerid, SLOT_TRYING)
			
			//TextDrawSetString(Text:TextDrawMainInfo(playerid), Edycja akcesoria ~g~aktywna~w~, ponizej przedstawiona zostala ~r~legenda~w~.~n~~n~~y~~k~~PED_JUMPING~ ~w~- anuluj~n~~y~~k~~VEHICLE_ENTER_EXIT~ ~w~- akceptuj~n~~n~~y~~k~~SNEAK_ABOUT~ + STRZALKA ~w~- pozycjonowanie~n~~y~~k~~PED_SPRINT~ + STRZALKA ~w~- skalowanie)
			//TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			return 1
		)
	)
	if(dialogid == D_RADIO_OPTIONS)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					ShowPlayerDialog(playerid, D_RADIO_SET_CANAL, DIALOG_STYLE_INPUT, CB radio » Ustaw kanał, Wprowadź numer kanału, z którym pragniesz się połączyć:, Dalej, Anuluj)
				)
				case 1:
				(
					ShowPlayerDialog(playerid, D_RADIO_BUY_CANAL, DIALOG_STYLE_INPUT, CB radio » Wykup kanał na własność, Wprowadź numer kanału, jaki zamierzasz zakupić na własność:, Dalej, Anuluj)
				)
				case 2:
				(
					ShowPlayerDialog(playerid, D_RADIO_CANAL_PASSWORD, DIALOG_STYLE_INPUT, CB radio » Ustaw hasło dla kanału, Wprowadź numer kanału, dla którego chcesz zmienić hasło:, Dalej, Anuluj)
				)
				case 3:
				(
					ShowPlayerDialog(playerid, D_RADIO_DELETE_CANAL, DIALOG_STYLE_INPUT, CB radio » Definitywnie usuń kanał, Wprowadź numer kanału, który chcesz usunąć:, Dalej, Anuluj)
				)
				case 4:
				(
					ShowPlayerDialog(playerid, D_RADIO_ASSIGN_CANAL, DIALOG_STYLE_INPUT, CB radio » Przypisz kanał pod grupę, Wprowadź numer kanału, który chcesz przypisać:, Dalej, Anuluj)
				)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_SET_CANAL)
	(
		if(response)
		(
			if(strlen(inputtext) ) 11 || strval(inputtext) (= 0)
			(
			 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Wprowadzono błędny numer kanału., OK, )
				return 1
			)
			vehid = GetPlayerVehicleID(playerid), radio_canal = strval(inputtext), data(64), string(128),
				channel_ownertype, channel_owner, channel_password(32)
				
			mysql_query_format(SELECT channel_ownertype, channel_owner, channel_password  FROM hrp_radio_channels WHERE channel_canal = %d LIMIT 1, radio_canal)
			
			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)dds(32), channel_ownertype, channel_owner, channel_password)
				
				if(channel_ownertype == OWNER_PLAYER || (channel_ownertype == OWNER_GROUP && IsPlayerInGroup(playerid, channel_owner)))
				(
					if(strlen(channel_password))
					(
						MainPlayerTable(playerid) = radio_canal
					
						format(string, sizeof(string), Wprowadź poniżej hasło dostępu dla kanału %d:, radio_canal)
						ShowPlayerDialog(playerid, D_RADIO_PASSWORD, DIALOG_STYLE_INPUT, Wprowadź hasło, Wprowadź poniżej hasło dostępu dla tego kanału:, Połącz, Anuluj)
					)
					else
					(
						CarInfo(vehid)(cRadioCanal) = radio_canal
					
	 					format(string, sizeof(string), Pomyślnie połączyłeś się z kanałem %d.\nUżyj komendy /cb, by porozumiewać się na kanale z innymi., radio_canal)
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
					)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Nie posiadasz odpowiednich uprawnień, by móc połączyć się z tym kanałem., OK, )
				)
			)
			else
			(
				CarInfo(vehid)(cRadioCanal) = radio_canal
				
				format(string, sizeof(string), Pomyślnie połączyłeś się z kanałem %d.\nUżyj komendy /cb, by porozumiewać się na kanale z innymi., radio_canal)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			)
			mysql_free_result()
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_PASSWORD)
	(
		if(response)
		(
			if(strlen(inputtext) )= 32 || strlen(inputtext) (= 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzone hasło jest nieprawidłowe., OK, )
				return 1
			)
			vehid = GetPlayerVehicleID(playerid), radio_canal = MainPlayerTable(playerid), channel_password(128), string(128)
			mysql_real_escape_string(inputtext, channel_password)
			
			mysql_query_format(SELECT channel_uid FROM hrp_radio_channels WHERE channel_canal = %d AND channel_password = %s LIMIT 1, radio_canal, channel_password)

			mysql_store_result()
			if(mysql_num_rows() != 0)
			(
				CarInfo(vehid)(cRadioCanal) = radio_canal
			
   				format(string, sizeof(string), Pomyślnie połączyłeś się z kanałem %d.\nUżyj komendy /cb, by porozumiewać się na kanale z innymi., radio_canal)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzone hasło jest nieprawidłowe., OK, )
			)
			mysql_free_result()
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_BUY_CANAL)
	(
		if(response)
		(
	 		if(strlen(inputtext) ) 11 || strval(inputtext) (= 0)
			(
			 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Wprowadzono błędny numer kanału., OK, )
				return 1
			)
			radio_canal = strval(inputtext), string(128)
			mysql_query_format(SELECT channel_uid FROM hrp_radio_channels WHERE channel_canal = %d LIMIT 1, radio_canal)
			
			mysql_store_result()
			if(mysql_num_rows() != 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ten kanał jest niedostępny., OK, )
			)
			else
			(
				MainPlayerTable(playerid) = radio_canal
			
				format(string, sizeof(string), Czy jesteś pewien, że chcesz kupić kanał %d na własność? Koszt: $250., radio_canal)
				ShowPlayerDialog(playerid, D_RADIO_ACCEPT_CANAL, DIALOG_STYLE_MSGBOX, CB radio » Wykup kanał na własność, string, Tak, Nie)
			)
			mysql_free_result()
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_ACCEPT_CANAL)
	(
		if(response)
		(
			if(PlayerCache(playerid)(pCash) ( 250)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Nie posiadasz takiej ilości gotówki., OK, )
				return 1
			)
			radio_canal = MainPlayerTable(playerid), string(128)
			mysql_query_format(INSERT INTO hrp_radio_channels VALUES (, %d, %d, %d, ), radio_canal, OWNER_PLAYER, PlayerCache(playerid)(pUID))

			hrp_GivePlayerMoney(playerid, -250)
			
			format(string, sizeof(string), Wykupiłeś kanał %d na własność. W opcjach CB radio możesz nim zarządzać., radio_canal)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_CANAL_PASSWORD)
	(
		if(response)
		(
   			if(strlen(inputtext) ) 11 || strval(inputtext) (= 0)
			(
			 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Wprowadzono błędny numer kanału., OK, )
				return 1
			)
			radio_canal = strval(inputtext), data(32), string(256),
				channel_ownertype, channel_owner
				
			mysql_query_format(SELECT channel_ownertype, channel_owner FROM hrp_radio_channels WHERE channel_canal = %d LIMIT 1, radio_canal)
			
			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)dd, channel_ownertype, channel_owner)
				
				if((channel_ownertype == OWNER_PLAYER && channel_owner == PlayerCache(playerid)(pUID)) || (channel_ownertype == OWNER_GROUP && IsPlayerPermissedGroup(playerid, channel_owner, PERM_LEADER)))
				(
					MainPlayerTable(playerid) = radio_canal
				
					format(string, sizeof(string), Wprowadź poniżej hasło, jakie chcesz ustawić dla kanału %d.\nPuste pole całkowicie zdejmuje hasło dla kanału.\n\nHasło nie może przekroczyć 32 znaków., radio_canal)
					ShowPlayerDialog(playerid, D_RADIO_SET_PASSWORD, DIALOG_STYLE_INPUT, CB radio » Ustaw hasło dla kanału, string, Ustaw, Anuluj)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie masz odpowiednich uprawnień, by móc zmienić hasło dla tego kanału., OK, )
				)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie masz odpowiednich uprawnień, by móc zmienić hasło dla tego kanału., OK, )
			)
			mysql_free_result()
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_SET_PASSWORD)
	(
		if(response)
		(
  			if(strlen(inputtext) )= 32)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Podane hasło jest za długie., OK, )
				return 1
			)
			radio_canal = MainPlayerTable(playerid), string(128)
			
   			if(strlen(inputtext))
			(
				channel_password(128)
		   		mysql_real_escape_string(inputtext, channel_password)
			
				mysql_query_format(UPDATE hrp_radio_channels SET channel_password = %s WHERE channel_canal = %d LIMIT 1, channel_password, radio_canal)

				format(string, sizeof(string), Hasło dla kanału %d zostało pomyślnie zmienione.\nNowe hasło to: %s, radio_canal, channel_password)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			)
			else
			(
				mysql_query_format(UPDATE hrp_radio_channels SET channel_password =  WHERE channel_canal = %d LIMIT 1, radio_canal)
			
				format(string, sizeof(string), Hasło dla kanału %d zostało pomyślnie zdjęte., radio_canal)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_DELETE_CANAL)
	(
		if(response)
		(
			if(strlen(inputtext) ) 11 || strval(inputtext) (= 0)
			(
			 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Wprowadzono błędny numer kanału., OK, )
				return 1
			)
			radio_canal = strval(inputtext), data(32), string(128),
				channel_ownertype, channel_owner

			mysql_query_format(SELECT channel_ownertype, channel_owner FROM hrp_radio_channels WHERE channel_canal = %d LIMIT 1, radio_canal)

			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)dd, channel_ownertype, channel_owner)

				if((channel_ownertype == OWNER_PLAYER && channel_owner == PlayerCache(playerid)(pUID)) || (channel_ownertype == OWNER_GROUP && IsPlayerPermissedGroup(playerid, channel_owner, PERM_LEADER)))
				(
					MainPlayerTable(playerid) = radio_canal
				
					format(string, sizeof(string), Czy jesteś pewien, że chcesz definitywnie usunąć kanał %d?, radio_canal)
					ShowPlayerDialog(playerid, D_RADIO_DELETE_ACCEPT, DIALOG_STYLE_MSGBOX, CB radio » Definitywnie usuń kanał, string, Tak, Nie)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień, by móc usunąć ten kanał., OK, )
				)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień, by móc usunąć ten kanał., OK, )
			)
			mysql_free_result()
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_DELETE_ACCEPT)
	(
		if(response)
		(
			radio_canal = MainPlayerTable(playerid), string(64)
			mysql_query_format(DELETE FROM hrp_radio_channels WHERE channel_canal = %d LIMIT 1, radio_canal)

			format(string, sizeof(string), Kanał %d został definitywnie usunięty., radio_canal)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_ASSIGN_CANAL)
	(
		if(response)
		(
  			if(strlen(inputtext) ) 11 || strval(inputtext) (= 0)
			(
			 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapił błąd, Wprowadzono błędny numer kanału., OK, )
				return 1
			)
			radio_canal = strval(inputtext), data(32),
				channel_ownertype, channel_owner

			mysql_query_format(SELECT channel_ownertype, channel_owner FROM hrp_radio_channels WHERE channel_canal = %d LIMIT 1, radio_canal)

			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)dd, channel_ownertype, channel_owner)

				if(channel_ownertype == OWNER_PLAYER && channel_owner == PlayerCache(playerid)(pUID))
				(
					MainPlayerTable(playerid) = radio_canal
					
			   		list_groups(256), group_id_fix
					format(list_groups, sizeof(list_groups), (C0C0C0)Slot\tNazwa oraz UID grupy(FFFFFF))

					for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
					(
						if(PlayerGroup(playerid)(slot)(gUID))
			  			(
			  				group_id_fix = PlayerGroup(playerid)(slot)(gID)
							format(list_groups, sizeof(list_groups), %s\n%d\t%s (%d), list_groups, slot + 1, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			 			)
					)
					ShowPlayerDialog(playerid, D_RADIO_ASSIGN_ACCEPT, DIALOG_STYLE_LIST, CB radio » Przypisz kanał pod grupę, list_groups, Wybierz, Anuluj)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień, by móc przypisać ten kanał., OK, )
				)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień, by móc przypisać ten kanał., OK, )
			)
			mysql_free_result()
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_RADIO_ASSIGN_ACCEPT)
	(
		if(response)
		(
			group_slot = strval(inputtext) - 1, radio_canal = MainPlayerTable(playerid), string(128)
			if(group_slot ( 0)
			(
				GameTextForPlayer(playerid, ~r~Anulowano., 3000, 3)
				return 1
			)
			group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
			if(!IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień dla tej grupy., OK, )
				return 1
			)
			mysql_query_format(UPDATE hrp_radio_channels SET channel_ownertype = %d, channel_owner = %d WHERE channel_canal = %d LIMIT 1, OWNER_GROUP, GroupData(group_id_fix)(gUID), radio_canal)

			format(string, sizeof(string), Kanał %d został pomyślnie przypisany pod grupę.\nKanał przypisano dla grupy %s (UID: %d)., radio_canal, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_TAXI_CORP)
	(
		if(response)
		(
			if(!strval(inputtext))
			(
				return 1
			)
			group_id_fix = strval(inputtext), string(256)
			PlayerCache(playerid)(pAlarmCall) = group_id_fix
			
			format(string, sizeof(string), Dodzwoniłeś się do %s znajdujacego się w Los Santos.\nPodaj szczegółowo miejsce położenia w jakim się znajdujesz, a my wyślemy do Ciebie taksówkę., GroupData(group_id_fix)(gName))
			ShowPlayerDialog(playerid, D_TAXI_CALL, DIALOG_STYLE_INPUT, Taxi, string, Dalej, Anuluj)
			return 1
		)
		else
		(
  			MainPlayerTable(playerid) = 0
			PlayerCache(playerid)(pAlarmCall) = INVALID_PLAYER_ID

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
			RemovePlayerAttachedObject(playerid, SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_PLAYER_STATS)
	(
		if(response)
		(
			list_item = strval(inputtext)
			if(list_item == 1)
			(
				if(PlayerCache(playerid)(pWalkAnim))
				(
					PlayerCache(playerid)(pWalkAnim) = 0
					SavePlayerStats(playerid, SAVE_PLAYER_OPTIONS)
					
					GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~w~Animacja chodzenia ~r~wylaczona, 3000, 3)
					return 1
				)
			
				list_anims(2048)
				for (anim_id = 1 anim_id ( MAX_ANIMATIONS anim_id++)
				(
					format(list_anims, sizeof(list_anims), %s\n%s, list_anims, AnimInfo(anim_id)(aCommand))
				)
				if(strlen(list_anims))
				(
					ShowPlayerDialog(playerid, D_SELECT_WALK_ANIM, DIALOG_STYLE_LIST, Lista animacji:, list_anims, Wybierz, Zamknij)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znaleziono żadnych animacji., OK, )
				)
				return 1
			)
			if(list_item == 3)
			(
				// edycja FPS
				if(GetViewMode(playerid) == MODE_FIRSTPERSON)
				(
					SetThirdPerson(playerid, 1)
					SyncCamera(playerid)
				)
				else
				(
					SetThirdPerson(playerid, 0)
					SyncCamera(playerid)
				)
			)
			
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_WALK_ANIM)
	(
		if(response)
		(
			PlayerCache(playerid)(pWalkAnim) = AnimInfo(listitem + 1)(aUID)
			SavePlayerStats(playerid, SAVE_PLAYER_OPTIONS)
			
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~w~Animacja chodzenia ~g~wlaczona, 3000, 3)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_LIST_ITEMS)
	(
		if(response)
		(
			if(listitem == 0)
			(
				cmd_p(playerid, podnies)
				return 1
			)

			if(listitem == 1)
			(
				ListPlayerCheckedItems(playerid)
				return 1
			)
			
			if(listitem == 2)
			(
				return 1
			)
			
			if(!strval(inputtext))
			(
				return 1
			)
			item_uid = strval(inputtext), itemid = GetItemID(item_uid), title(64), list_manage(256)
			PlayerCache(playerid)(pManageItem) = itemid

			format(title, sizeof(title), Zarządzaj przedmiotem » %s (UID: %d), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID))

			if(ItemInfo(itemid)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestań używać tego przedmiotu\n2. (FF3D3D)Odłóż przedmiot w pobliżu(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Pokaż informacje(FFFFFF)\n5. (FF3D3D)Włóż do innego przedmiotu(FFFFFF)\n6. (FF3D3D)Wsadź przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmień opis przedmiotu\n9. Pokaż przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. Użyj tego przedmiotu\n2. Odłóż przedmiot w pobliżu\n3. Sprzedaj innemu graczowi\n(93A818)4. Pokaż informacje(FFFFFF)\n5. Włóż do innego przedmiotu\n6. Wsadź przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmień opis przedmiotu\n9. Pokaż przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróć)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_MANAGE_ITEM)
	(
		if(response)
		(
			list_item = strval(inputtext), itemid = PlayerCache(playerid)(pManageItem)

			if(list_item == 1)
			(
				OnPlayerUseItem(playerid, itemid)
				return 1
			)

			if(list_item == 2)
			(
				if(ItemInfo(itemid)(iUsed))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz odłożyć tego przedmiotu., OK, )
					return 1
				)
				OnPlayerDropItem(playerid, itemid, false)
				return 1
			)

			if(list_item == 3)
			(
				if(ItemInfo(itemid)(iUsed))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz sprzedać tego przedmiotu., OK, )
					return 1
				)

				list_players(256)
				foreach(Player, i)
				(
	   				if(Logged(i) && Spawned(i))
		   			(
			  			if(i != playerid)
						(
							if(PlayerToPlayer(5.0, playerid, i))
							(
								format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, i, PlayerName(i))
							)
						)
	  				)
			   	)
		   		if(!strlen(list_players))
				(
	  				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znaleziono żadnych graczy w pobliżu., OK, )
				)
				ShowPlayerDialog(playerid, D_OFFER_ITEM_PLAYER, DIALOG_STYLE_LIST, Sprzedaj przedmiot:, list_players, Oferuj, Anuluj)
				return 1
			)

			if(list_item == 4)
			(
				ShowPlayerItemInfo(playerid, itemid)
				return 1
			)

			if(list_item == 5)
			(
				if(ItemInfo(itemid)(iUsed) || ItemInfo(itemid)(iType) == ITEM_BAG)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz włożyć tego przedmiotu., OK, )
					return 1
				)

				data(64), list_items(256),
					item_uid, item_name(32)

				mysql_query_format(SELECT item_uid, item_name FROM hrp_items WHERE item_place = %d AND item_owner = %d AND item_type = %d, PLACE_PLAYER, PlayerCache(playerid)(pUID), ITEM_BAG)

				mysql_store_result()
				while(mysql_fetch_row(data, |))
				(
					sscanf(data, p(|)ds(32), item_uid, item_name)
					format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, item_uid, item_name)
				)
				mysql_free_result()
				if(strlen(list_items))
				(
					ShowPlayerDialog(playerid, D_PUT_ITEM_BAG, DIALOG_STYLE_LIST, Włóż przedmiot:, list_items, Wybierz, Anuluj)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz przedmiotu, do którego możesz coś włożyć., OK, )
				)
				return 1
			)

			if(list_item == 6)
			(
   				if(ItemInfo(itemid)(iUsed))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz wsadzić tego przedmiotu do schowka., OK, )
					return 1
				)
				doorid = GetPlayerDoorID(playerid)
		 		if(doorid == -1)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Musisz znajdować się w budynku, aby móc schować przedmiot., OK, )
					return 0
				)
		   		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie jesteś właścicielem tego budynku., OK, )
					return 0
				)
				if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie jesteś właścicielem tego budynku., OK, )
					return 0
				)
				if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
				(
					if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie jesteś właścicielem tego budynku., OK, )
						return 1
					)
				)

				mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_SAFE, DoorData(doorid)(dUID), ItemInfo(itemid)(iUID))

				ItemInfo(itemid)(iUID) = 0

				ItemInfo(itemid)(iValue1) = 0
				ItemInfo(itemid)(iValue2) = 0

				ItemInfo(itemid)(iType) = 0

				ItemInfo(itemid)(iPlace) = 0
				ItemInfo(itemid)(iOwner) = 0

				ItemInfo(itemid)(iUsed) = 0
				ItemInfo(itemid)(iChecked) = false
				
				Itter_Remove(Items, itemid)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przedmiot został schowany w schowku.\nAby wyjąć, wpisz /drzwi schowek w budynku., OK, )
				return 1
			)
			
			if(list_item == 7)
			(
				if(ItemInfo(itemid)(iType) != ITEM_CIGGY && ItemInfo(itemid)(iType) != ITEM_DRUG)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ten przedmiot nie może zostać podzielony., OK, )
					return 1
				)
				MainPlayerTable(playerid) = itemid
				
				if(ItemInfo(itemid)(iType) == ITEM_CIGGY)
				(
					ShowPlayerDialog(playerid, D_DIVIDE_ITEM, DIALOG_STYLE_INPUT, Rozdzielanie przedmiotu, Wpisz liczbę sztuk do oddzielenia, OK, Anuluj)
				)
				else if(ItemInfo(itemid)(iType) == ITEM_DRUG)
				(
					ShowPlayerDialog(playerid, D_DIVIDE_ITEM, DIALOG_STYLE_INPUT, Rozdzielanie przedmiotu, Wpisz liczbę gram do oddzielenia, OK, Anuluj)
				)
				return 1
			)
			
			if(list_item == 8)
			(
				if(ItemInfo(itemid)(iType) == ITEM_CORPSE)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz zmienić opisu tego przedmiotu., OK, Anuluj)
					return 1
				)
				ShowPlayerDialog(playerid, D_ADD_ITEM_DESC, DIALOG_STYLE_INPUT, Opis przedmiotu, Wpisz opis przedmiotu (max. 128 znaków)., OK, Anuluj)
				return 1
			)
			
			if(list_item == 9)
			(
				list_players(256)
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerToPlayer(10.0, playerid, i))
						(
							format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, i, PlayerName(i))
						)
					)
				)
				if(strlen(list_players))
				(
					ShowPlayerDialog(playerid, D_SHOW_ITEM_INFO_TO, DIALOG_STYLE_LIST, Gracze znajdujący się w pobliżu:, list_players, PW, Zamknij)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_INPUT, Wystąpił błąd, W pobliżu Ciebie nie ma żadnego gracza, któremu możesz pokazać przedmiot., OK, Anuluj)
					return 1
				)
			)
			
			bGUI_ListPlayerItems(playerid,PlayerCache(playerid)(pItemPage))
			return 1
		)
		else
		(
			switch(PlayerCache(playerid)(pInterface))
			(
				case INTERFACE_TYPE_TEXT:
				(
					ListPlayerItems(playerid, MANAGE_TYPE_ALL)
				)
				case INTERFACE_TYPE_GRAPHIC:
				(
					// trzeba dodać odświeżanie kursora, jednocześnie nie psując całego efektu
					SelectTextDraw(playerid, 0x8C8C8CFF)
					//
					bGUI_ListPlayerItems(playerid,PlayerCache(playerid)(pItemPage))
				)
			)
			return 1
		)
	)
	if(dialogid == D_SHOW_ITEM_INFO_TO)
	(
		if(response)
		(
			clickedplayerid = strval(inputtext),
				line(64),
				itemid = PlayerCache(playerid)(pManageItem)
			
			format(line, sizeof(line), przedmiot %d %d, ItemInfo(itemid)(iUID), clickedplayerid)
			cmd_pokaz(playerid, line)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ADD_ITEM_DESC)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				itemid = PlayerCache(playerid)(pManageItem)
				MagicQuotes(inputtext)
				mysql_query_format(UPDATE hrp_items SET item_desc = %s WHERE item_uid = %d, inputtext, ItemInfo(itemid)(iUID))
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Opis przedmiotu uległ zmianie., OK, )
				return 1
			)
			else
			(
				return 1
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_OFFER_ITEM_PLAYER)
	(
		if(response)
		(
			MainPlayerTable(playerid) = strval(inputtext)
			ShowPlayerDialog(playerid, D_OFFER_ITEM_PRICE, DIALOG_STYLE_INPUT, Sprzedaj przedmiot » Cena, Wprowadź poniżej cenę, jaką oczekujesz w zamian za przedmiot:, Oferuj, Anuluj)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_OFFER_ITEM_PRICE)
	(
		if(response)
		(
			price = strval(inputtext), itemid = PlayerCache(playerid)(pManageItem), giveplayer_id = MainPlayerTable(playerid)
			if(price ( 0 || strlen(inputtext) ) 11)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wprowadzono nieprawidłową kwotę., OK, )
				return 1
			)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_ITEM, ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), price)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CHECK_ITEM)
	(
		if(response)
		(
			string(256)
			if(listitem == 0)
			(
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				(
 					Float:PosX, Float:PosY, Float:PosZ, Float:PosA, virtual_world = GetPlayerVirtualWorld(playerid),
 						object_id, checked_items, item_next

					GetPlayerPos(playerid, PosX, PosY, PosZ)
					GetPlayerFacingAngle(playerid, PosA)

					foreach(Items, itemid)
					(
						if(ItemInfo(itemid)(iUID))
						(
							if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
							(
								if(!ItemInfo(itemid)(iUsed))
								(
									if(ItemInfo(itemid)(iChecked))
									(
										mysql_query_format(UPDATE hrp_items SET item_posx = %f, item_posy = %f, item_posz = %f, item_place = %d, item_world = %d WHERE item_uid = %d LIMIT 1, PosX, PosY, PosZ, PLACE_NONE, virtual_world, ItemInfo(itemid)(iUID))
										if(ItemInfo(itemid)(iType) == ITEM_WEAPON || ItemInfo(itemid)(iType) == ITEM_PAINT)
										(
											object_id = CreateDynamicObject(WeaponModel(ItemInfo(itemid)(iValue1)), PosX + random(2), PosY + random(2), PosZ - 1.0, 80.0, 0.0, -PosA, virtual_world, -1, -1, 80.0)
										)
										else if(ItemInfo(itemid)(iType) == ITEM_TUNING)
										(
											object_id = CreateDynamicObject(ItemInfo(itemid)(iValue1), PosX + random(2), PosY + random(2), PosZ - 0.5, 0.0, 0.0, -PosA, virtual_world, -1, -1, 80.0)
										)
										else
										(
		  									object_id = CreateDynamicObject(ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjModel), PosX + random(2), PosY + random(2), PosZ - 1.0, ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjRotX), ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjRotY), -PosA, virtual_world, -1, -1, 80.0)
										)

										Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, (ItemInfo(itemid)(iUID) * -1))
										Streamer_Update(playerid)

										hrp_ItemActionLog(%s (UID: %d) odlozyl przedmiot %s (UID: %d) na ziemie (PosX: %.3f, PosY: %.3f, PosZ: %.3f)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), PosX, PosY, PosZ)

										ItemInfo(itemid)(iUID) = 0
										ItemInfo(itemid)(iValue1) = 0
										ItemInfo(itemid)(iValue2) = 0
										ItemInfo(itemid)(iType) = 0

										ItemInfo(itemid)(iPlace) = 0
										ItemInfo(itemid)(iOwner) = 0

										ItemInfo(itemid)(iUsed) = 0
										ItemInfo(itemid)(iChecked) = false

										Itter_SafeRemove(Items, itemid, item_next)
										checked_items ++

										itemid = item_next
									)
								)
							)
						)
					)
					if(!checked_items)
					(
						GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~w~Brak ~r~zaznaczonych ~w~przedmiotow., 2000, 3)
						ListPlayerCheckedItems(playerid)
					)
					else
					(
						format(string, sizeof(string), * %s coś odkłada., PlayerName(playerid))
						ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)

						ApplyAnimation(playerid,BOMBER,BOM_Plant,4.1,0,0,0,0,0,1)
					)

				)
				else if(IsPlayerInAnyVehicle(playerid))
				(
					vehid = GetPlayerVehicleID(playerid), checked_items, item_next
  					foreach(Items, itemid)
					(
						if(ItemInfo(itemid)(iUID))
						(
							if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
							(
								if(!ItemInfo(itemid)(iUsed))
								(
									if(ItemInfo(itemid)(iChecked))
									(
										mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_VEHICLE, CarInfo(vehid)(cUID), ItemInfo(itemid)(iUID))
										hrp_ItemActionLog(%s (UID: %d) odlozyl przedmiot %s (UID: %d) w pojezdzie %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))

										ItemInfo(itemid)(iUID) = 0
										ItemInfo(itemid)(iValue1) = 0
										ItemInfo(itemid)(iValue2) = 0
										ItemInfo(itemid)(iType) = 0

										ItemInfo(itemid)(iPlace) = 0
										ItemInfo(itemid)(iOwner) = 0

										ItemInfo(itemid)(iUsed) = 0
										ItemInfo(itemid)(iChecked) = false

										Itter_SafeRemove(Items, itemid, item_next)
										checked_items ++

										itemid = item_next
									)
								)
							)
						)
					)
					if(!checked_items)
					(
						GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~w~Brak ~r~zaznaczonych ~w~przedmiotow., 2000, 3)
						ListPlayerCheckedItems(playerid)
					)
					else
					(
						format(string, sizeof(string), * %s odkłada coś w pojeździe., PlayerName(playerid))
						FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)

						ApplyAnimation(playerid,BOMBER,BOM_Plant,4.1,0,0,0,0,0,1)
					)
				)
				return 1
			)

			if(listitem == 1)
			(
				doorid = GetPlayerDoorID(playerid), item_next
		 		if(doorid == -1)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Musisz znajdować się w budynku, aby móc schować przedmiot., OK, )
					return 1
				)
		   		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie jesteś właścicielem tego budynku., OK, )
					return 1
				)
				if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie jesteś właścicielem tego budynku., OK, )
					return 1
				)
				if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
				(
					if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie jesteś właścicielem tego budynku., OK, )
						return 1
					)
				)

				foreach(Items, itemid)
				(
					if(ItemInfo(itemid)(iUID))
					(
						if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
						(
							if(!ItemInfo(itemid)(iUsed))
							(
								if(ItemInfo(itemid)(iChecked))
								(
									mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_SAFE, DoorData(doorid)(dUID), ItemInfo(itemid)(iUID))

									ItemInfo(itemid)(iUID) = 0

									ItemInfo(itemid)(iValue1) = 0
									ItemInfo(itemid)(iValue2) = 0

									ItemInfo(itemid)(iType) = 0

									ItemInfo(itemid)(iPlace) = 0
									ItemInfo(itemid)(iOwner) = 0

									ItemInfo(itemid)(iUsed) = 0
									ItemInfo(itemid)(iChecked) = false

									Itter_SafeRemove(Items, itemid, item_next)
									itemid = item_next
								)
							)
						)
					)
				)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wybrane przedmioty zostały schowane w schowku.\nAby ujrzeć listę przedmotów w schowku, skorzystaj z komendy /drzwi schowek., OK, )
				return 1
			)

			if(listitem == 2)
			(
				return 1
			)

			item_uid = strval(inputtext), itemid = GetItemID(item_uid)
			if(ItemInfo(itemid)(iChecked))
			(
		 		ItemInfo(itemid)(iChecked) = false
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~w~Przedmiot ~r~odznaczony, 2000, 3)
			)
			else
			(
				ItemInfo(itemid)(iChecked) = true
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~w~Przedmiot ~g~zaznaczony, 2000, 3)
			)
			ListPlayerCheckedItems(playerid)
			return 1
		)
		else
		(
			ListPlayerItems(playerid, MANAGE_TYPE_ALL)
			return 1
		)
	)
	if(dialogid == D_LIST_ITEMS_USE)
	(
		if(response)
		(
	 		if(listitem == 0)
			(
				cmd_p(playerid, podnies)
				return 1
			)

			if(listitem == 1)
			(
				ListPlayerCheckedItems(playerid)
				return 1
			)

			if(listitem == 2)
			(
				return 1
			)
			
			if(!strval(inputtext))
			(
				return 1
			)
			item_uid = strval(inputtext), itemid = GetItemID(item_uid)
			OnPlayerUseItem(playerid, itemid)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_LIST_ITEMS_DROP)
	(
		if(response)
		(
   			if(listitem == 0)
			(
				cmd_p(playerid, podnies)
				return 1
			)

			if(listitem == 1)
			(
				return 1
			)

			if(listitem == 2)
			(
				return 1
			)
			
			if(!strval(inputtext))
			(
				return 1
			)
			item_uid = strval(inputtext), itemid = GetItemID(item_uid)
			OnPlayerDropItem(playerid, itemid, false)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CHANGE_GROUP_TYPE)
	(
		if(response)
		(
			group_id_fix = MainPlayerTable(playerid), group_type = strval(inputtext) - 1, string(128)

			
			GroupData(group_id_fix)(gType) = group_type
			SaveGroup(group_id_fix)
			
			format(string, sizeof(string), Typ grupy %s (SampID: %d, UID: %d) został pomyślnie zmieniony na %s., GroupData(group_id_fix)(gName), group_id_fix, GroupData(group_id_fix)(gUID), GroupTypeInfo(GroupData(group_id_fix)(gType))(gTypeName))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_MANAGE_GROUPS)
	(
		if(response)
		(
			if(listitem == 0)
			(
				return 1
			)
			group_slot = strval(inputtext) - 1, string(64), list_manage(256)
			MainPlayerTable(playerid) = group_slot

			group_id_fix = PlayerGroup(playerid)(group_slot)(gID)

			format(string, sizeof(string), Zarządzaj grupą » %s (UID: %d), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))

			strcat(list_manage, 1. Pokaż informacje\n)
			strcat(list_manage, 2. Opuść grupę\n)
			strcat(list_manage, 3. Członkowie online\n)
			strcat(list_manage, 4. Ubranie grupowe\n)
			strcat(list_manage, 5. Ogłoszenia\n)
			
			if(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER)
			(
				if(!GroupData(group_id_fix)(gOwner))
				(
					strcat(list_manage, 6. Stwórz podgrupę\n)
					strcat(list_manage, 7. Lista grup podrzędnych\n)
					strcat(list_manage, 8. Dodaj ogłoszenie\n)
				)
			)
			ShowPlayerDialog(playerid, D_GROUP_OPTIONS, DIALOG_STYLE_LIST, string, list_manage, Wybierz, Anuluj)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_GROUP_OPTIONS)
	(
		if(response)
		(
			group_slot = MainPlayerTable(playerid), group_id_fix = PlayerGroup(playerid)(group_slot)(gID),
				string(256)

			switch(listitem)
			(
				case 0:
				(
					ShowPlayerGroupInfo(playerid, group_id_fix)
				)
				case 1:
				(
					format(string, sizeof(string), Czy jesteś pewien że chcesz opuścić grupę %s (UID: %d)?, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
					ShowPlayerDialog(playerid, D_LEAVE_GROUP, DIALOG_STYLE_MSGBOX, Opuść grupę, string, Tak, Nie)
				)
				case 2:
				(
					format(string, sizeof(string), %d online, group_slot + 1)
					cmd_g(playerid, string)
				)
				case 3:
				(
					if(!PlayerGroup(playerid)(group_slot)(gSkin))
					(
						GameTextForPlayer(playerid, ~r~Brak ustalonego ~w~ubrania, 3000, 3)
						return 1
					)
					SetPlayerSkin(playerid, PlayerGroup(playerid)(group_slot)(gSkin))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przebrałeś się w strój służbowy.\nAby powrócić do starego ubrania skorzystaj z /przebierz., OK, )
				)
				case 4:
				(
					format(string, sizeof(string), %d ogloszenia, group_slot + 1)
					cmd_g(playerid, string)
				)
				case 5:
				(
					subgroups_count
					foreach(Groups, g)
					(
						if(GroupData(g)(gUID))
						(
							if(GroupData(g)(gOwner) == GroupData(group_id_fix)(gUID))
							(
								subgroups_count ++
							)
						)
					)
					if(subgroups_count )= 5)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Limit podgrup tej grupy został wyczerpany (maksymalnie 5)., OK, )
						return 1
					)
					format(string, sizeof(string), %s (UID: %d) » Dodaj podgrupę, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
					ShowPlayerDialog(playerid, D_ADD_SUBGROUP, DIALOG_STYLE_INPUT, string, Wprowadź nazwę nowej podgrupy.\nNazwa nie może przekroczyć 32 znaków., Dodaj, Anuluj)
	   			)
				case 6:
				(
					list_groups(256)
					foreach(Groups, g)
					(
						if(GroupData(g)(gUID))
						(
							if(GroupData(g)(gOwner) == GroupData(group_id_fix)(gUID))
							(
								format(list_groups, sizeof(list_groups), %s\n%d\t%s, list_groups, GroupData(g)(gUID), GroupData(g)(gName))
							)
						)
					)
					if(!strlen(list_groups))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znaleziono żadnych podgrup dla tej grupy., OK, )
						return 1
					)
					format(string, sizeof(string), %s (UID: %d) » Lista grup podrzędnych, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
					ShowPlayerDialog(playerid, D_SUBGROUP_LIST, DIALOG_STYLE_LIST, string, list_groups, Info, Zamknij)
				)
				case 7:
				(
					MainPlayerTable(playerid) = PlayerGroup(playerid)(group_slot)(gID)
					ShowPlayerDialog(playerid, D_ADD_GROUP_ANN, DIALOG_STYLE_INPUT, Dodaj ogłoszenie, Wprowadź treść ogłoszenia widzialnego przez wszystkich członków grupy.\nPamiętaj, że dodając kolejne ogłoszenie, poprzednie będą widoczne tylko w panelu., OK, Anuluj)
				)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_LEAVE_GROUP)
	(
		if(response)
		(
			group_slot = MainPlayerTable(playerid), group_id_fix = PlayerGroup(playerid)(group_slot)(gID), string(128)

	   		PlayerGroup(playerid)(group_slot)(gUID) = 0
			PlayerGroup(playerid)(group_slot)(gID) = 0

			PlayerGroup(playerid)(group_slot)(gPerm) = 0
	  		strmid(PlayerGroup(playerid)(group_slot)(gTitle), Brak, 0, 4, 32)

			PlayerGroup(playerid)(group_slot)(gPayment) = 0
			mysql_query_format(DELETE FROM hrp_char_groups WHERE char_uid = %d AND group_uid = %d, PlayerCache(playerid)(pUID), GroupData(group_id_fix)(gUID))

			format(string, sizeof(string), Opuściłeś grupę. Slot %d jest teraz wolny., group_slot + 1)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			hrp_GroupActionLog(%s (UID: %d) opuscil dobrowolnie grupe %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ADD_SUBGROUP)
	(
		if(response)
		(
	 		if(strlen(inputtext) )= 32 || strlen(inputtext) (= 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Podana nazwa dla grupy jest nieprawidłowa., OK, )
				return 1
			)
			group_slot = MainPlayerTable(playerid), group_id_fix = PlayerGroup(playerid)(group_slot)(gID),
					string(256)
				
			created_group_id_fix = CreateGroup(inputtext)
			
			GroupData(created_group_id_fix)(gOwner) = GroupData(group_id_fix)(gUID)
			GroupData(created_group_id_fix)(gType)  = GroupData(group_id_fix)(gType)
			
			SaveGroup(created_group_id_fix)
			
			format(string, sizeof(string), Pomyślnie dodano nową podgrupę dla %s (UID: %d).\n\nNazwa podgrupy: %s\nIdentyfikator (UID): %d\n\nAby zarządzać podgrupą wejdź do panelu grupowego., GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), GroupData(created_group_id_fix)(gName), GroupData(created_group_id_fix)(gUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			hrp_GroupActionLog(%s (UID: %d) utworzyl podgrupe %s (UID: %d) dla grupy %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), GroupData(created_group_id_fix)(gName), GroupData(created_group_id_fix)(gUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SUBGROUP_LIST)
	(
		if(response)
		(
			group_uid = strval(inputtext), group_id_fix = GetGroupID(group_uid)
			ShowPlayerGroupInfo(playerid, group_id_fix)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_BOOTH_NUMBER)
	(
		// WAŻNE !!! phoneid = ID BUDKI Z KTÓREJ DZWONISZ ... phone = ID Z BUDKI NA KTÓRˇ DZWONISZ!!!
		if(response)
		(
			phoneid = MainPlayerTable(playerid)
				MainPlayerTable(playerid) = 0

			string(128)
			if(strlen(inputtext) ) 7 || strlen(inputtext) (= 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Podany numer jest nieprawidłowy., OK, )
				return 1
			)

			number = strval(inputtext)

			if(Phones(phoneid)(phoneNumber) == number)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Podany numer jest nieprawidłowy., OK, )
				return 1	
			)

			callid = -1
			
			if(number ) 999999)
			(
				if(PlayerCache(playerid)(pCash) ( 10)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie masz wystarczające ilości gotówki. Kosz użycia budki to $10., OK, )
					return 1
				)
				// Dzwoni do budki
				foreach(Phones, phone)
				(
					if(Phones(phone)(phoneNumber) == number)
					(
						callid = Itter_Free(Calls)
						
						Call(callid)(caller) = playerid
						
						Call(callid)(called) = INVALID_PLAYER_ID
						Call(callid)(calledNumber) = number
						Call(callid)(calledDevice) = DEVICE_BOX
						Call(callid)(calledDevID) = phone
						break
					)
				)
			)
			else if(number ) 999 && number ( 9999)
			(
				// Dzwoni na stacjonarny
				for(i = 0  i ( MAX_HOMEPHONES i++)
				(
					if(HomePhones(i)(hPhoneNumber) == number)
					(
						callid = Itter_Free(Calls)
						
						Call(callid)(caller) = playerid
						
						Call(callid)(called) = INVALID_PLAYER_ID
						Call(callid)(calledNumber) = number
						Call(callid)(calledDevice) = DEVICE_HOME
						Call(callid)(calledDevID) = i
						break
					)
				)
			)
			else if(number ) 9999 && number ( 99999)
			(
				// pager
				foreach(Items, itemid)
				(
					if(ItemInfo(itemid)(iUID))
					(
						if(ItemInfo(itemid)(iType) == ITEM_PAGER && ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iValue1) == number)
						(
							foreach(Player, i)
							(
								if(ItemInfo(itemid)(iOwner) == PlayerCache(i)(pUID))
								(
									format(string, sizeof(string), ** Twój pager pokazał na ekranie numer %d. **, Phones(phoneid)(phoneNumber))
									SendClientMessage(i, COLOR_LIGHTRED, string)

									SendClientMessage(playerid, COLOR_DO, ** W słuchawce słychać dĽwięk potwierdzenia połączenia. **)
									return 1
								)
							)
							return 1
						)
					)
				)
			)
			else if(number ) 99 && number (= 999)
			(
				PlayerCache(playerid)(pSerivceNumberAs) = Phones(phoneid)(phoneNumber)
				// Dzwoni na numer alarmowy/sklep/taxi/etc.
				if(number == 777)
				(
					list_taxi_corp(1024)
					foreach(Groups, group_id_fix)
					(
						if(GroupData(group_id_fix)(gUID))
						(
							if(GroupData(group_id_fix)(gType) == GROUP_TAXI)
							(
								workers = 0
								foreach(Player, i)
								(
									if(Logged(i) && Spawned(i))
									(
										if(PlayerCache(i)(pGroupDuty) == GroupData(group_id_fix)(gUID))
										(
						 					workers ++
										)
									)
								)
								if(workers)
								(
									format(list_taxi_corp, sizeof(list_taxi_corp), %s\n%d\t(na służbie %d)\t%s, list_taxi_corp, group_id_fix, workers, GroupData(group_id_fix)(gName))
								)
							)
						)
					)
					if(strlen(list_taxi_corp))
					(
			  			//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
						//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
						attachPlayerPhone(playerid)
					
						ShowPlayerDialog(playerid, D_SELECT_TAXI_CORP, DIALOG_STYLE_LIST, Korporacje taksówkarskie, list_taxi_corp, Dalej, Anuluj)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, W chwili obecnej nie ma żadnej taksówki na służbie., OK, )
					)
					return 1
				)
				if(number == 911)
				(
					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)
					
					SendClientMessage(playerid, COLOR_YELLOW, Sekretarka: Witaj, połączyłeś się z numerem alarmowym centrali Los Santos, z kim połączyć?)
					ShowPlayerDialog(playerid, D_ALARM_NUMBER, DIALOG_STYLE_LIST, Z kim chcesz się połączyć?, Los Santos Police Department\nLos Santos Medical Center\nLos Santos Fire Department\nDepartment Of Sanitation Electricity, Wybierz, Anuluj)
					return 1
				)
				if(number == 444)
				(
					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)

					ShowPlayerDialog(playerid, D_SN_CALL, DIALOG_STYLE_INPUT, Los Santos News, Dodzwoniłeś się do radiostacji w Los Santos.\nPowiedz nam po krótce w czym rzecz., Dalej, Anuluj)
					return 1
				)
			)
			else if(number ) 99999 && number (= 999999)
			(
				if(PlayerCache(playerid)(pCash) ( 10)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie masz wystarczające ilości gotówki. Kosz użycia budki to $10., OK, )
					return 1
				)
				// Dzwoni na komórkę
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pPhoneNumber) == number)
						(
							if(PlayerCache(i)(pCall) != -1)
							(
								SendClientMessage(playerid, COLOR_DO, ** Słychać sygnał zajętości... **)
							)
							else
							(
								callid = Itter_Free(Calls)
								
								Call(callid)(caller) = playerid
						
								Call(callid)(called) = i
								Call(callid)(calledNumber) = PlayerCache(i)(pPhoneNumber)
								Call(callid)(calledDevice) = DEVICE_CELL
							)
							break
						)
					)
				)
			)

			if(callid != -1)
			(
				if(Phones(phoneid)(phoneBusy))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Ktoś już używa tej budki., OK, )
					EndCall(callid)
					return 0
				)

				Call(callid)(caller) = playerid
				Call(callid)(callerNumber) = Phones(phoneid)(phoneNumber)
				Call(callid)(callerDevice) = DEVICE_BOX
				Call(callid)(callerDevID) = phoneid
				//Call(callid)(convo) = false		//blint kurwa 3 - tutaj tego nie bylo
				
				if(Call(callid)(calledDevice) == DEVICE_HOME)
				(
					foreach(Player, i)
					(
						if(CanPlayerHearHomephone(i, Call(callid)(calledDevID)))
						(
							SendClientMessage(i, COLOR_DO, ** Słychać dźwięk dzwoniącego telefonu domowego. **)
							PlayerPlaySound(i, 20600, 0.0, 0.0, 0.0)
						)
					)
				)

				if(Call(callid)(calledDevice) == DEVICE_BOX)
				(
					// Dzwonek budki dla wszystkich
					foreach(Player, i)
					(
						if(CanPlayerHearPhone(i, Call(callid)(calledDevID)))
						(
							SendClientMessage(i, COLOR_DO, ** Słyszysz dźwięk telefonu w pobliżu. Brzmi jak budka telefoniczna. **)
							PlayerPlaySound(i, 20600, 0.0, 0.0, 0.0)
						)
					)

				)
				else if(Call(callid)(calledDevice) == DEVICE_CELL)
				(
					// Dzwonek komórki dla gracza
					format(string, sizeof(string), * Słychać dźwięk dzwoniącego telefonu. (( %s )), PlayerName(Call(callid)(called)))
					ProxDetector(10.0, Call(callid)(called), string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, false)

					// Audio dzwonka
					Float:PosX, Float:PosY, Float:PosZ
					GetPlayerPos(Call(callid)(called), PosX, PosY, PosZ)

					foreach(Player, player)
					(
						if(Logged(player) && Spawned(player))
						(
							if(IsPlayerInRangeOfPoint(player, 10.0, PosX, PosY, PosZ))
							(
								// Miejsce na dźwięk dzwonienia
								//audio = Audio_Play(player, AUDIO_CALLING)
								//Audio_Set3DPosition(player, audio, PosX, PosY, PosZ, 10.0)
							)
						)
					)
				)

				//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
				//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
				attachPlayerPhone(playerid)

				Phones(phoneid)(phoneBusy) = true

				SendClientMessage(playerid, COLOR_DO, * Słychać sygnał próby połączenia się... *)

				format(string, sizeof(string), Połączenie przychodzące od %d, użyj /odbierz, by odebrać rozmowę., Phones(phoneid)(phoneNumber))
				SendClientMessage(Call(callid)(called), COLOR_YELLOW, string)
				
				PlayerCache(playerid)(pUsingBooth) = true
				PlayerCache(playerid)(pCall) = callid
				hrp_GivePlayerMoney(playerid, -2)

				Itter_Add(Calls, callid)
				return 1
			)

			SendClientMessage(playerid, COLOR_DO, * Nie można połączyć się z wybranym numerem...)
			return 1

		)
		else
		(
			return 1
		)
		
	)
	if(dialogid == D_DESC_OPTIONS)
	(
		if(response)
		(
			about_data(128), string(512)
			switch(listitem)
			(
				case 0:
				(
					qLimit = 0
					if(PlayerCache(playerid)(pPremium))
					(
						qLimit = 10
					)
					else
					(
						qLimit = 3
					)
					mysql_query_format(SELECT about_uid, about_name FROM hrp_abouts WHERE about_owner = %d ORDER BY about_uid DESC LIMIT %d, PlayerCache(playerid)(pUID), qLimit)
					mysql_store_result()

					while(mysql_fetch_row(about_data, |))
					(
						about_uid, about_name(32)
						sscanf(about_data, p(|)ds(32), about_uid, about_name)
						format(string, sizeof(string), %s\n%d. %s, string, about_uid, about_name)
					)
					
					mysql_free_result()
					
					if(strlen(string) ) 0)
					(
						ShowPlayerDialog(playerid, D_DESC_LIST, DIALOG_STYLE_LIST, Lista opisów, string, Wybierz, Zamknij)
						return 1
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz jeszcze żadnych opisów., OK, )
						return 1
					)
				)
				case 1:
				(
					desc_count = 0
					mysql_query_format(SELECT count(about_uid) FROM hrp_abouts WHERE about_owner = %d LIMIT 1, PlayerCache(playerid)(pUID))
					mysql_store_result()

					if(mysql_fetch_row(about_data, |))
				 	(
				  		sscanf(about_data, p(|)d, desc_count)
					)
					mysql_free_result()

					if(PlayerCache(playerid)(pPremium))
					(
						if(desc_count )= 10)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Posiadasz już 10 opisów. Usuń jeden aby dodać kolejny., OK, )
						)
					)
					else
					(
						if(desc_count )= 3)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Posiadasz już 3 opisy. Usuń jeden aby dodać kolejny lub wykup konto premium ale zwiększyć limit do 10 opisów., OK, )
						)
					)
					ShowPlayerDialog(playerid, D_DESC_ADD, DIALOG_STYLE_INPUT, Dodaj opis, Wprowadź tekst opisu do dodania., Dodaj, Anuluj)
				)
				case 2:
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Aktualny opis, PlayerCache(playerid)(pDescTagText), OK, )
					return 1
				)
				case 3:
				(
			  		format(PlayerCache(playerid)(pDescTagText), 128,  )
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Opis został pomyślnie usunięty., OK, )
					return 1
				)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DESC_ADD)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				format(MainPlayerStringTable(playerid), 512, %s, inputtext)
				ShowPlayerDialog(playerid, D_DESC_ADDNAME, DIALOG_STYLE_INPUT, Dodaj nazwę opisu, Wprowadź nazwę opisu do dodania., Dodaj, Anuluj)
				return 1
			)
			else
			(
				return 1
			)
		)
	)
	if(dialogid == D_DESC_ADDNAME)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
			    descEscaped(512),
					descContent(512)
			    
				mysql_real_escape_string(inputtext, descEscaped)
				mysql_real_escape_string(MainPlayerStringTable(playerid), descContent)
				
				mysql_query_format(INSERT INTO hrp_abouts (about_content, about_name, about_owner) VALUES(%s, %s, %d), descContent, descEscaped, PlayerCache(playerid)(pUID))
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Opis został pomyślnie dodany., OK, )
			)
			else
			(
				return 1
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DESC_LIST)
	(
		if(response)
		(
			MainPlayerTable(playerid) = strval(inputtext)
			ShowPlayerDialog(playerid, D_DESC_ACTIONS, DIALOG_STYLE_LIST, Edytor opisów » Akcja, 1. Ustaw\n2. Zobacz\n3. Usuń, Wybierz, Anuluj)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DESC_ACTIONS)
	(
		if(response)
		(
			about_data(256), about_content(128), about_name(32)
			mysql_query_format(SELECT about_content, about_name FROM hrp_abouts WHERE about_uid = %d LIMIT 1, MainPlayerTable(playerid))
			mysql_store_result()

			if(mysql_fetch_row(about_data, |))
		 	(
		  		sscanf(about_data, p(|)s(128)s(32), about_content, about_name)
			)
			mysql_free_result()
			switch(listitem)
			(
				case 0:
				(
					cmd_opis(playerid, about_content)
					return 1
				)
				case 1:
				(
					ShowPlayerDialog(playerid, D_DESC_SHOW, DIALOG_STYLE_MSGBOX, about_name, about_content, OK, )
					return 1
				)
				case 2:
				(
					mysql_query_format(DELETE FROM hrp_abouts WHERE about_uid = %d LIMIT 1, MainPlayerTable(playerid))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Opis został poprawnie usunięty., OK, )
					return 1
				)
			)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DESC_SHOW)
	(
		if(response)
		(
			ShowPlayerDialog(playerid, D_DESC_ACTIONS, DIALOG_STYLE_LIST, Edytor opisów » Akcja, 1. Ustaw\n2. Zobacz\n3. Usuń, Wybierz, Anuluj)
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_PICK_STYLE)
	(
		if(response)
		(			
			switch(listitem)
			(
				case 0:
				(
					SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL)
					PlayerCache(playerid)(pFightingStyle) = FIGHT_STYLE_NORMAL
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoim stylem walki stał się styl podstawowy., OK, )
				)
				case 1:
				(
					if(PlayerCache(playerid)(pKnownStyles) & FIGHT_BOX)
					(
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING)
						PlayerCache(playerid)(pFightingStyle) = FIGHT_STYLE_BOXING
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoim stylem walki stał się box., OK, )
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie umiesz jeszcze tego stylu. Udaj się na siłownie aby się go nauczyć., OK, )
					)
				)
				case 2:
				(
					if(PlayerCache(playerid)(pKnownStyles) & FIGHT_KUNGFU)
					(
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU)
						PlayerCache(playerid)(pFightingStyle) = FIGHT_STYLE_KUNGFU
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoim stylem walki stało się Kung Fu., OK, )
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie umiesz jeszcze tego stylu. Udaj się na siłownie aby się go nauczyć., OK, )
					)
				)
				case 3:
				(
					if(PlayerCache(playerid)(pKnownStyles) & FIGHT_KICKBOX)
					(
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD)
						PlayerCache(playerid)(pFightingStyle) = FIGHT_STYLE_KNEEHEAD
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoim stylem walki stał się Kickboxing., OK, )
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie umiesz jeszcze tego stylu. Udaj się na siłownie aby się go nauczyć., OK, )
					)
				)
				case 4:
				(
					if(PlayerCache(playerid)(pKnownStyles) & FIGHT_ULTI)
					(
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK)
						PlayerCache(playerid)(pFightingStyle) = FIGHT_STYLE_GRABKICK
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoim stylem walki stał się styl uliczny, OK, )
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie umiesz jeszcze tego stylu. Udaj się na siłownie aby się go nauczyć., OK, )
					)
				)
			)
			return 1
		)
	)
	if(dialogid == D_SWEEP_ACCEPT)
	(
		if(response)
		(
			Float:rX(2), Float:rY(2), Float:rZ(2), rPointName(2)(64), data(256), i
			mysql_query(SELECT p_rid FROM hrp_sweep_points ORDER BY RAND() LIMIT 1)
			mysql_store_result()
			mysql_fetch_field(p_rid, data)
			PlayerCache(playerid)(pSweepRoute) = strval(data)
			mysql_free_result()
			
			mysql_query_format(SELECT p_name, p_posx, p_posy, p_posz FROM hrp_sweep_points WHERE p_rid = %d ORDER BY p_id ASC, PlayerCache(playerid)(pSweepRoute))
			mysql_store_result()
			
			PlayerCache(playerid)(pSweepSteps) = mysql_num_rows()

			while(mysql_fetch_row(data, |))
			(
				if(i ) 1) break
				sscanf(data, p(|)s(64)fff, rPointName(i), rX(i), rY(i), rZ(i))
				i++
			)
			
			mysql_free_result()
			
			PlayerCache(playerid)(pSweepTime) = gettime()
			PlayerCache(playerid)(pSweepStep) = 0
			PlayerCache(playerid)(pSweep) = true
			SetPlayerRaceCheckpoint(playerid, 0, rX(0), rY(0), rZ(0), rX(1), rY(1), rZ(1), 5.0)
			
			format(data, sizeof(data), Podjales sie pracy sprzatacza ulic. Udaj się do punktu ~r~%s ~w~i podazaj za intrukcjami. Niech ulice beda z Toba., rPointName(0))
			TextDrawSetString(Text:TextDrawMainInfo(playerid), data)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			PlayerCache(playerid)(pShowInfoText) = 7
		)
		else
		(
			RemovePlayerFromVehicle(playerid)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, W związku z odrzucenie przez Ciebie pracy sprzątacza ulic, urząd nie pozwala Ci na wynajem ich wozów., OK, )
		)
		return 1
	)
	if(dialogid == D_DIVIDE_ITEM)
	(
		if(response)
		(
			itemid = MainPlayerTable(playerid), portion = strval(inputtext), string(128)
			if(portion (= 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Stary taka porcja nie przejdzie. Odstaw to bo źle na Ciebie wpływa., OK, )
				return 1
			)
			SecondPlayerTable(playerid) = portion
			
			if(ItemInfo(itemid)(iType) == ITEM_CIGGY)
			(
				format(string, sizeof(string), Wpisz liczbę porcji zawierających %d sztuk., portion)
			)
			else if(ItemInfo(itemid)(iType) == ITEM_DRUG)
			(
				format(string, sizeof(string), Wpisz liczbę porcji zawierających %d gram., portion)
			)
			ShowPlayerDialog(playerid, D_DIVIDE_ITEM_FINAL, DIALOG_STYLE_INPUT, Dzielenie przedmiotów, string, OK, )
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_DIVIDE_ITEM_FINAL)
	(
		if(response)
		(
			itemid = MainPlayerTable(playerid), portion = SecondPlayerTable(playerid), portions = strval(inputtext)
			if(portions (= 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Stary taka porcja nie przejdzie. Odstaw to bo źle na Ciebie wpływa., OK, )
			)
			if(ItemInfo(itemid)(iUID))
			(
				if(ItemInfo(itemid)(iType) == ITEM_CIGGY)
				(
					if(portion * portions (= ItemInfo(itemid)(iValue1))
					(
						for(i = 0 i ( portions i++)
						(
							CreatePlayerItem(playerid, ItemInfo(itemid)(iName), ItemInfo(itemid)(iType), portion, 0)
							ItemInfo(itemid)(iValue1) -= portion
						)
						if(ItemInfo(itemid)(iValue1) (= 0)
						(
							DeleteItem(ItemInfo(itemid)(iUID))
						)
						mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Sukces, Podział przedmiotu udał się., OK, )
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Stary taka porcja nie przejdzie. Odstaw to bo źle na Ciebie wpływa., OK, )
						return 1
					)
				)
				else if(ItemInfo(itemid)(iType) == ITEM_DRUG)
				(
					if(portion * portions (= ItemInfo(itemid)(iValue2))
					(
						
						for(i = 0 i ( portions i++)
						(						
							ItemInfo(itemid)(iValue2) -= portion
							item_uid = CreatePlayerItem(playerid, temp, ItemInfo(itemid)(iType), ItemInfo(itemid)(iValue1), portion)
							c_item_id = GetItemID(item_uid)
							GenerateDrugNameByItemid(c_item_id)
						)
						
						mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
						if(ItemInfo(itemid)(iValue2) (= 0)
						(
							DeleteItem(ItemInfo(itemid)(iUID))
						)
						else
						(
							GenerateDrugNameByItemid(itemid)
						)
						
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Sukces, Podział przedmiotu udał się., OK, )
						MainPlayerTable(playerid) = 0
						SecondPlayerTable(playerid) = 0
						return 1
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Stary taka porcja nie przejdzie. Odstaw to bo źle na Ciebie wpływa., OK, )
						MainPlayerTable(playerid) = 0
						SecondPlayerTable(playerid) = 0
						return 1
					)
				)
			) else (
				MainPlayerTable(playerid) = 0
				SecondPlayerTable(playerid) = 0
				return 1
			)
		)
		else
		(
			MainPlayerTable(playerid) = 0
			SecondPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_ADD_GROUP_ANN)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				group_id_fix = MainPlayerTable(playerid)
				uid = CreateAnn(GroupData(group_id_fix)(gUID), PlayerCache(playerid)(pUID), inputtext)
				if(uid)
				(
					string(128)
					foreach(Player, i)
					(
						if(IsPlayerPermissedGroup(i, GroupData(group_id_fix)(gUID), PERM_CHAT))
						(
							format(string, sizeof(string), Gracz %s (ID: %d) dodał właśnie ogłoszenie w Twojej grupie:, PlayerName(playerid), playerid)
							SendClientMessage(i, COLOR_RED, string)
							SendClientMessage(i, COLOR_ORANGE, inputtext)
						)
					)
					
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Sukces, Ogłoszenie zostało dodane poprawnie.\nMożesz je zobaczyć pod /g (slot) ogloszenie., OK, )
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Wystąpił błąd przy dodawaniu Twojego ogłoszenia.\nSkontaktuj się z Administratorem., OK, )
				)
				MainPlayerTable(playerid) = 0
			)
			else
			(
				MainPlayerTable(playerid) = 0
				return 1
			)
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_SPRAY_FONT)
	(
		if(response)
		(
			PlayerCache(playerid)(pTaggingFont) = listitem
			ShowPlayerDialog(playerid, D_SPRAY_FONT_SIZE, DIALOG_STYLE_LIST, Wybierz czcionkę dla tego tagu, 0 - 10px\n1 - 11px\n2 - 12px\n3 - 13px\n4 - 14px\n5 - 15px\n6 - 16px\n7 - 17px\n8 - 18px\n9 - 19px\n10 - 20px\n11 - 21px\n12 - 22px\n13 - 23px\n14 - 24px\n15 - 25px\n16 - 26px\n17 - 27px\n18 - 28px\n19 - 29px\n20 - 30px, Maluj, Anuluj)
		)
		return 1
	)
	if(dialogid == D_SPRAY_FONT_SIZE)
	(
		if(response)
		(
			PlayerCache(playerid)(pTaggingSize) = listitem
			ShowPlayerDialog(playerid, D_SPRAY, DIALOG_STYLE_INPUT, Tworzenie tagu, Wpisz treść tagu, który chcesz namalować na ścanie., Maluj, Anuluj)
		)
		return 1
	)
	if(dialogid == D_SPRAY)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				Float:PosX, Float:PosY, Float:PosZ, itemid = MainPlayerTable(playerid)
				GetPlayerPos(playerid, PosX, PosY, PosZ)
				GetXYInFrontOfPlayer(playerid, PosX, PosY, 2.0)
				object_id = hrp_AddObject(18661, PosX, PosY, PosZ, 0.0, 0.0, 0.0, 0, 0), Float:angle
				GetPlayerFacingAngle(playerid, angle)
				SetDynamicObjectRot(object_id, 0.0, 0.0, angle + 90.0)
				Streamer_Update(playerid)
				
				//SetObjectMaterialText(object_id, inputtext, 0, OBJECT_MATERIAL_SIZE_256x128, Arial, 24, 1, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER)
				SetDynamicObjectMaterialText(object_id, 0,  , OBJECT_MATERIAL_SIZE_256x128, Fonts(PlayerCache(playerid)(pTaggingFont)), FontSizes(PlayerCache(playerid)(pTaggingSize)), 1, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER)
				object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
				mysql_query_format(INSERT INTO hrp_tags (tag_objectuid, tag_owner, tag_text, tag_size, tag_font) VALUE(%d, %d, %s, %d, %d), object_uid, PlayerCache(playerid)(pUID), inputtext, PlayerCache(playerid)(pTaggingSize), PlayerCache(playerid)(pTaggingFont))

				TextDrawSetString(Text:TextDrawMainInfo(playerid), Maluj swoj tag do wyczerpania puszki z farba. Nastepnie ustaw go w odpowiednim miejscu.)
				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
				PlayerCache(playerid)(pShowInfoText) = 8
				
				PlayerCache(playerid)(pTagging) = object_id
				ItemInfo(itemid)(iValue1) = 41
				ItemInfo(itemid)(iValue2) = 1000 // ok. 30 sekund
				
				
				mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))

				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = ItemInfo(itemid)(iUID)				
				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = ItemInfo(itemid)(iValue1)
				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = ItemInfo(itemid)(iValue2)
				WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
				
				GivePlayerWeapon(playerid, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iValue2))
				
				WeaponCache(playerid)(WEAPON_FUNC)(pEquipped) = true
				
				//DeleteItem(ItemInfo(itemid)(iUID))
				MainPlayerTable(playerid) = 0
				return 1
			)
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_PD_CAR_NAME_INPUT)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				if(strcmp(inputtext, LS, true))
				(
					uid, search(8), data(128), name(24), plate(8), owner_name(64), model, fuel_type, owner, owner_type
					
					strmid(search, inputtext, 2, strlen(inputtext), sizeof(search))
					mysql_query_format(SELECT car_uid, car_name, car_model, car_fueltype, car_owner, car_ownertype FROM hrp_cars WHERE car_uid = %s, search)
				
					mysql_store_result()
					if(mysql_fetch_row(data, |))
					(
						sscanf(data, p(|)ds(24)dddd, uid, name, model, fuel_type, owner, owner_type)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, LSPD )) Kartoteka )) Informacja, Brak rezultatow dla podanych danych., OK, )
					)
					mysql_free_result()
					
					if(owner_type == OWNER_PLAYER)
					(
						mysql_query_format(SELECT char_name FROM hrp_characters WHERE char_uid = %d, owner)
						mysql_store_result()
						if(mysql_fetch_row(data, |))
						(
							sscanf(data, p(|)s(64), owner_name)
						)
						else
						(
							format(owner_name, sizeof(owner_name), Brak danych)
						)
						mysql_free_result()
					)
					else if(owner_type == OWNER_GROUP)
					(
						mysql_query_format(SELECT group_name FROM hrp_groups WHERE group_uid = %d, owner)
						mysql_store_result()
						if(mysql_fetch_row(data, |))
						(
							sscanf(data, p(|)s(64), owner_name)
						)
						else
						(
							format(owner_name, sizeof(owner_name), Brak danych)
						)
						mysql_free_result()
					)
					
					format(plate, sizeof(plate), LS%d, uid)
					
					PD_ShowCarRecord(playerid, name, plate, owner_name, model, fuel_type)
					
					return 1
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, LSPD )) DMV )) Informacja, Brak rezultatow dla podanych danych., OK, )
				)
			)
			else
			(
				PD_Hide(playerid)
				PlayerCache(playerid)(pPDMenu) = 0
				return 1
			)
		)
		else
		(
			PD_Hide(playerid)
			PlayerCache(playerid)(pPDMenu) = 0
			return 1
		)
	)
	if(dialogid == D_FCK_CONFIRM)
	(
		if(response)
		(
			ShowPlayerDialog(playerid, D_FCK_REASON, DIALOG_STYLE_INPUT, FCK, Opisz okoliczności śmierci w max. 128 znakach, OK, Anuluj)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_FCK_REASON)
	(
		// FCK wpisane przez arczira (bo nikt inny nie blokuje)
		if(response)
		(
			giveplayer_id = MainPlayerTable(playerid),
				killer_uid = PlayerCache(giveplayer_id)(pKiller),
				weapon_uid = PlayerCache(giveplayer_id)(pKillerWeapon)
			
			TogglePlayerControllable(giveplayer_id, false)
			DropAllPlayerItems(giveplayer_id)
			item_uid = CreatePlayerCorpse(giveplayer_id, killer_uid, weapon_uid)
			
			ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postać została uśmiercona.\nOd tej pory postać, która została uśmiercona jest już nieaktywna.\n\nZostajesz wyrzucony z serwera., OK, )
			hrp_Block(giveplayer_id, playerid, Dynamiczne FCK, BLOCK_CHAR, 0, true)
			Kick(giveplayer_id)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Gnój dostał FCK. Dobra robota mój panie., OK, )
			MainPlayerTable(playerid) = 0
			
			SetItemDesc(item_uid, inputtext)
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_FCK_REASON_P)
	(
		// FCK wpisane przez gracza
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				killer_uid = PlayerCache(playerid)(pKiller),
					weapon_uid = PlayerCache(playerid)(pKillerWeapon)
				
				DropAllPlayerItems(playerid)
				item_uid = CreatePlayerCorpse(playerid, killer_uid, weapon_uid)
				
				SetItemDesc(item_uid, inputtext)
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postać została uśmiercona.\nOd tej pory postać, która została uśmiercona jest już nieaktywna.\n\nZostajesz wyrzucony z serwera., OK, )
				hrp_Block(playerid, -1, CK, BLOCK_CHAR, 0, true)
				Kick(playerid)
				return 1
			)
			return 1
		)
		return 1
	)
	if(dialogid == D_DESTROY_CAR)
	(
		if(response)
		(
			vehid = MainPlayerTable(playerid), sell_price = SecondPlayerTable(playerid)
			
			hrp_GivePlayerMoney(playerid, sell_price)
			DeleteVehicle(vehid)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pojazd został zezłomowany., OK, )
		
			MainPlayerTable(playerid) = 0
			SecondPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			SecondPlayerTable(playerid) = 0
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wróć kiedy zmienisz zdanie., OK, )
			return 1
		)
	)
	if(dialogid == D_PD_NAME_INPUT)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				if(strlen(inputtext) ) 32)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Zbyt długi tekst., OK, )
					return 1
				)
				if(!strcmp(inputtext, dodaj, true))
				(
					ShowPlayerDialog(playerid, D_PD_C_ADD_NEW, DIALOG_STYLE_INPUT, LSPD )) Kartoteka )) Dodaj, Wpisz \Imie_Nazwisko\ dodawanej osoby., Szukaj, Anuluj)
					return 1
				)
			
				search(512), data(128), name(32), counter, id, num
				mysql_real_escape_string(inputtext, inputtext)
				mysql_query_format(SELECT id, nick FROM lspd_records WHERE nick LIKE %%%s%%, inputtext)
			
				mysql_store_result()
				num = mysql_num_rows()
				if(num != 0)
				(
					while(mysql_fetch_row(data, |))
					(
						sscanf(data, p(|)ds(32), id, name)
						if(counter + 1 == num)
						(
							format(search, sizeof(search), %s%d - %s, search, id, name)
						)
						else
						(
							format(search, sizeof(search), %s%d - %s\n, search, id, name)
						)
						counter++
					)
					ShowPlayerDialog(playerid, D_PD_C_SEARCH_RESULT, DIALOG_STYLE_LIST, LSPD )) Kartoteka )) Szukaj, search, OK, Anuluj)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, LSPD )) Kartoteka )) Informacja, Brak rezultatow dla podanych danych., OK, )
				)
				mysql_free_result()
				return 1
			)
			else
			(
				PD_Hide(playerid)
				return 1
			)
		)
		else
		(
			PD_Hide(playerid)
			return 1
		)
	)
	if(dialogid == D_PD_C_ADD_NEW)
	(
		if(response)
		(
			if(strlen(inputtext) )= 3 && strlen(inputtext) (= 32)
			(
				d, m, y, h, i, s, times(32) getdate(d, m, y) gettime(h, i, s)
				format(times, sizeof(times), %d-%d-%d %d:%d:%d, d, m, y, h, i, s)
				
				MagicQuotes(inputtext)
				
				mysql_query_format(INSERT INTO lspd_records (id, nick, author, date) VALUES(NULL, %s, %s, %s), inputtext, PlayerName(playerid), times)
				new_id = mysql_insert_id()
				
				if(new_id) (
					MainPlayerTable(playerid) = new_id
					showDataFor(playerid, new_id)
					return 1
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wystąpił nieznany błąd. Pisz do Sim00na i zanotuj czas dodania., OK, )
					return 1
				)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wpis musi mieć minimum 3 znaki i maximum 32 znaki., OK, )
				return 1
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_PD_C_LIST)
	(
		if(response)
		(
			option = strval(inputtext)
			if(option == 0)
			(
				ShowPlayerDialog(playerid, D_PD_C_ADD_FIELD, DIALOG_STYLE_INPUT, LSPD )) Kartoteka )) Dodaj, Wpisz nazwę nowego pola., Dodaj, Anuluj)
				return 1
			)
			else
			(
				showDataForRecord(playerid, option)
				return 1
			)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wszystkie zmiany zostały zapisane., OK, )
			return 1
		)
	)
	if(dialogid == D_PD_C_ADD_FIELD)
	(
		if(response)
		(
			if(strlen(inputtext) )= 3 && strlen(inputtext) (= 32)
			(
				record = MainPlayerTable(playerid)
				mysql_real_escape_string(inputtext, inputtext)
				MagicQuotes(inputtext)
				mysql_query_format(INSERT INTO lspd_record (id, record, name, content) VALUES(NULL, %d, %s, Brak danych), record, inputtext)
				
				new_id = mysql_insert_id()
				SecondPlayerTable(playerid) = new_id
				
				string(128)
				format(string, sizeof(string), Wpisz dane poasujące do pola %s, inputtext)
				ShowPlayerDialog(playerid, D_PD_C_ADD_DATA, DIALOG_STYLE_INPUT, LSPD )) Kartoteka )) Dodaj, string, Dodaj, Anuluj)
				return 1
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wpis musi mieć minimum 3 znaki i maximum 32 znaki., OK, )
				return 1
			)
		)
	)
	if(dialogid == D_PD_C_ADD_DATA)
	(
		if(response)
		(
			if(strlen(inputtext) )= 3 && strlen(inputtext) (= 254)
			(
				record = MainPlayerTable(playerid), updating = SecondPlayerTable(playerid)
				mysql_real_escape_string(inputtext, inputtext)
				MagicQuotes(inputtext)
				mysql_query_format(UPDATE lspd_record SET content = %s WHERE id = %d, inputtext, updating)
				
				showDataFor(playerid, record)
				return 1
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wpis musi mieć minimum 3 znaki i maximum 32 znaki., OK, )
				return 1
			)
		)
	)
	if(dialogid == D_PD_C_RECORD)
	(
		id = MainPlayerTable(playerid)
		showDataFor(playerid, id)
		return 1
	)
	if(dialogid == D_PD_C_SEARCH_RESULT)
	(
		if(response)
		(
			option = strval(inputtext)
			if(option)
			(
				MainPlayerTable(playerid) = option
				showDataFor(playerid, option)
				return 1
			)
			return 1
		)
	)
	if(dialogid == D_BW_LIST)
	(
		if(response)
		(
			option = strval(inputtext), string(32)
			format(string, sizeof(string), zdejmij %d, option)
			cmd_bw(playerid, string)
			format(string, sizeof(string), %d 100, option)
			cmd_sethp(playerid, string)
			cmd_sethp(playerid, string)
		)
	)
	if(dialogid == D_LSPAD_PASSWORD)
	(
		if(response)
		(
			code = strval(inputtext),
				itemid = PlayerCache(playerid)(pLSPadItemID)

			if(ItemInfo(itemid)(iValue2) == code)
			(
				LSPad(playerid, 1)
			)
			else
			(
				ShowPlayerDialog(playerid, D_LSPAD_PASSWORD, DIALOG_STYLE_PASSWORD, ItemInfo(itemid)(iName), Wpisz kod do odblokowania urzadzenia., Odblokuj, Wyjdzź)
				return 1
			)
		)
	)
	if(dialogid == D_LSPAD_NEWPASSWORD)
	(
		if(response)
		(
			code = strval(inputtext),
				itemid = PlayerCache(playerid)(pLSPadItemID),
				ncode(8)
			
			if(code == 0)
			(
				ItemInfo(itemid)(iValue2) = 0
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Hasło zostało usuniete., OK, )

				format(ncode, sizeof(ncode), %s, Brak)
				PlayerTextDrawSetString(playerid, LSPad_SettingsCode, ncode)
			)
			else if(code ) 999 && code ( 10000)
			(
				ItemInfo(itemid)(iValue2) = code
				LSPad(playerid, 0)
				LSPad(playerid, 1, true)
			)
			else
			(
				ShowPlayerDialog(playerid, D_LSPAD_NEWPASSWORD, DIALOG_STYLE_INPUT, ItemInfo(itemid)(iName), Haslo niepoprawne!\n\nWpisz nowe 4-cyfrowe hasło lub 0 aby usunać hasło z urządzenia., Ustaw, Wyjdzź)
				return 1
			)

			mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
		)
		return 1
	)
	if(dialogid == D_GETZONE_MARIHUANA)
	(
		if(response)
		(
			mass = strval(inputtext)
			gangzone_id = GetCurrentPlayerGangZone(playerid)

			if(mass (= GangZoneInfo(gangzone_id)(gMarihuana))
			(
				GangZoneInfo(gangzone_id)(gMarihuana) -= mass
				SaveGangZone(gangzone_id, SAVE_GZ_THINGS)

				item_uid = CreatePlayerItem(playerid, Marihuana, ITEM_DRUG, DRUG_MARIHUANA, mass)
				c_item_id = GetItemID(item_uid)
				GenerateDrugNameByItemid(c_item_id)

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Trzymaj stary, tylko nie daj się złapać psiarni!, OK, )
				return 1
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Tyle nie dostaniesz. Nie spłaciłeś jeszcze ostatniej partii!, OK, )
				return 1	
			)
		)
		return 1
	)
	if(dialogid == D_GETZONE_AMP)
	(
		if(response)
		(
			mass = strval(inputtext)
			gangzone_id = GetCurrentPlayerGangZone(playerid)

			if(mass (= GangZoneInfo(gangzone_id)(gAmp))
			(
				GangZoneInfo(gangzone_id)(gAmp) -= mass
				SaveGangZone(gangzone_id, SAVE_GZ_THINGS)

				item_uid = CreatePlayerItem(playerid, Feta, ITEM_DRUG, DRUG_AMPHETAMINE, mass)
				c_item_id = GetItemID(item_uid)
				GenerateDrugNameByItemid(c_item_id)

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Trzymaj stary, tylko nie daj się złapać psiarni!, OK, )
				return 1
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Tyle nie dostaniesz. Nie spłaciłeś jeszcze ostatniej partii!, OK, )
				return 1	
			)
		)
		return 1
	)
	if(dialogid == D_GETZONE_METAAMP)
	(
		if(response)
		(
			mass = strval(inputtext)
			gangzone_id = GetCurrentPlayerGangZone(playerid)

			if(mass (= GangZoneInfo(gangzone_id)(gMetaamp))
			(
				GangZoneInfo(gangzone_id)(gMetaamp) -= mass
				SaveGangZone(gangzone_id, SAVE_GZ_THINGS)

				item_uid = CreatePlayerItem(playerid, Meta, ITEM_DRUG, DRUG_METAAMP, mass)
				c_item_id = GetItemID(item_uid)
				GenerateDrugNameByItemid(c_item_id)

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Trzymaj stary, tylko nie daj się złapać psiarni!, OK, )
				return 1
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Tyle nie dostaniesz. Nie spłaciłeś jeszcze ostatniej partii!, OK, )
				return 1	
			)
		)
		return 1
	)
	/*if(dialogid == D_BLACKJACK_INVITE)
	(
		if(response)
		(
			clickedplayerid = strval(inputtext)
			
			if(IsPlayerConnected(clickedplayerid))
			(
				printf((casino) %d w grze, clickedplayerid)
				if(Logged(clickedplayerid) && Spawned(clickedplayerid))
				(
					printf((casino) %d zalogowany i zrespawnowany, clickedplayerid)
					if(!PlayerCache(clickedplayerid)(pBW) && PlayerCache(clickedplayerid)(pCuffed) == INVALID_PLAYER_ID && PlayerCache(clickedplayerid)(pCuffedStill) == INVALID_PLAYER_ID)
					(
						printf((casino) %d nie ma bw, kajdanek, kajdanek still, clickedplayerid)
						if(!IsPlayerInAnyVehicle(clickedplayerid))
						(
							printf((casino) %d nie w pojeĽdzie, clickedplayerid)
							BJInviteToGame(playerid, clickedplayerid)
							return 1
						)
					)
				)
			)

			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie możesz teraz zaprosić tego gracza. Gracz nie może:\n\nByć niepodłączony, nie zalogowany lub nie zespawnowany\nNie może mieć BW lub być skutym\nNie może być w pojeĽdzie, OK, )
			return 1
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_BLACKJACK_CONFIRM)
	(
		if(response)
		(
			inviter = MainPlayerTable(playerid),
				stime = SecondPlayerTable(playerid)

			if(stime + 10 ( gettime()) (
				MainPlayerTable(playerid) = 0
				SecondPlayerTable(playerid) = 0
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, To zaporszenie straciło już swoją ważność., OK, )
				return 1
			)
			else
			(
				gameid = PlayerCache(inviter)(pCasinoGameID)
				BJAddPlayer(playerid, gameid)
				return 1
			)
		)
		else
		(

		)
	)*/
	if(dialogid == D_ZONE)
	(
		if(response)
		(
			option = strval(inputtext)
			
			if(option == 1)
			(
				// Atak

				gangzone_id = GetCurrentPlayerGangZone(playerid)
				if(GangZoneInfo(gangzone_id)(gUID))
				(
					d_group_id_fix = GetGroupID(GangZoneInfo(gangzone_id)(gOwner))
					a_group_id_fix = GetPlayerDutyGroupID(playerid)

					if(a_group_id_fix == INVALID_GROUP_ID)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Musisz być na duty gangu aby zaatakować teren., OK, )
						return 1
					)
					if(d_group_id_fix == INVALID_GROUP_ID)
					(
						GangZoneInfo(gangzone_id)(gOwner) = a_group_id_fix
						SaveGangZone(gangzone_id, SAVE_GZ_OWNER)
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ten teren nie należy do nikogo dlatego stałes sie jego właścicielem., OK, )
						return 1
					)

					if(GangZoneInfo(gangzone_id)(gAttack) + 60*60*48 ) gettime())
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ta strefa jest w tym momencie chroniona., OK, )
						return 1
					)

					a_count = 0, d_count = 0
					foreach(Player, i)
					(
						if(IsPlayerInGroup(i, GroupData(a_group_id_fix)(gUID)))
						(
							a_count++
						)
						if(IsPlayerInGroup(i, GroupData(d_group_id_fix)(gUID)))
						(
							d_count++
						)
					)

					if(a_count * 2 ) d_count || a_count ( 3 || d_count ( 3)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie ma wystarczająco graczy do walki lub atakujacych jest 2 raz wiecej niż broniacych., OK, )
						return 1
					)

					foreach(Gangbang, gbid)
					(
						if(Gangbang(gbid)(gbAttackingGroup) == a_group_id_fix)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja grupa jest już w walce!, OK, )
							return 1
						)
						if(Gangbang(gbid)(gbDefendingGroup) == d_group_id_fix)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ta grupa jest już w walce!, OK, )
							return 1
						)
					)

					gbid = Itter_Free(Gangbang)
					Gangbang(gbid)(gbAttackingGroup) = a_group_id_fix
					Gangbang(gbid)(gbDefendingGroup) = d_group_id_fix
					Gangbang(gbid)(gbZone) = gangzone_id
					Gangbang(gbid)(gbStartTime) = gettime()
					Gangbang(gbid)(gbAttackingDeaths) = 0
					Gangbang(gbid)(gbDefendingDeaths) = 0	

					Itter_Add(Gangbang, gbid)
				)



				cmd_strefy(playerid, show)
			)
			else if(option == 2)
			(
				// Oferuj terytorium
				cmd_strefy(playerid, show)

				list_players(256)
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerToPlayer(10.0, playerid, i))
						(
							format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, i, PlayerName(i))
						)
					)
				)
				if(strlen(list_players))
				(
					ShowPlayerDialog(playerid, D_GZ_OFFER, DIALOG_STYLE_LIST, Gracze znajdujący się w pobliżu:, list_players, Oferuj, Zamknij)
					return 1
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znaleziono graczy w pobliżu., OK, )
					return 1
				)
			)
			else if(option == 3)
			(
				// Poddaj terytorium
				cmd_strefy(playerid, show)
				ShowPlayerDialog(playerid, D_GZ_SURRENDER, DIALOG_STYLE_MSGBOX, Zarządzanie terenem, Czy jesteś pewny, że chcesz pozbyć się tego terenu?\nTa akcja jest nieodwracalna!, Tak, Nie)
				return 1
			)
			else if(option == 4)
			(
				// Wydaj ogłoszenie
				cmd_strefy(playerid, show)
				ShowPlayerDialog(playerid, D_GZ_MSG, DIALOG_STYLE_INPUT, Zarządzanie terenem, Wpisz wiadomość do wysłania, OK, Anuluj)
				return 1
			)
		)
		return 1
	)
	if(dialogid == D_GZ_OFFER)
	(
		if(response)
		(
			giveplayer_id = strval(inputtext)
			if(giveplayer_id != INVALID_PLAYER_ID && IsPlayerConnected(giveplayer_id))
			(
				offer_string(16)
				format(offer_string, sizeof(offer_string), teren %d 0, giveplayer_id)
				cmd_oferuj(playerid, offer_string)
				return 1
			)
		)
	)
	if(dialogid == D_GZ_SURRENDER)
	(
		if(response)
		(
			gangzone_id = GetCurrentPlayerGangZone(playerid)
			if(GangZoneInfo(gangzone_id)(gUID))
			(
				GangZoneInfo(gangzone_id)(gOwner) = 0
				SaveGangZone(gangzone_id, SAVE_GZ_OWNER)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Teren został poddany., OK, )
			)
			else
			(
				SendClientMessage(playerid, COLOR_RED, Nie buguj ...)
				return 1
			)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Postanowiłeą anulować akcje., OK, )
			return 1
		)
		return 1
	)
	if(dialogid == D_GZ_MSG)
	(
		if(response)
		(
			if(strlen(inputtext) ) 0)
			(
				gangzone_id = GetCurrentPlayerGangZone(playerid)
				if(GangZoneInfo(gangzone_id)(gUID))
				(
					if(IsPlayerPermissedGroup(playerid, GangZoneInfo(gangzone_id)(gOwner), PERM_LEADER))
					(
						foreach(Player, i)
						(
							if(IsPlayerInGangZone(i, gangzone_id))
							(
								SendClientMessage(i, COLOR_DO, ** Na miescie rozeszła się następująca plotka: **)
								SendClientMessage(i, COLOR_DO, inputtext)
							)
						)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informajca, Nie masz uprawnień do tej akcji., OK, )
					)
				)
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DOOR_ADDON_LIST)
	(
		if(response)
		(
			GuiMsg(playerid,Nie możesz wymontować tego akcesorium z budynku.,1)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DOOR_ADDON_MOUNT)
	(
		if(response)
		(
			addonID = MainPlayerTable(playerid), addonType = ItemInfo(addonID)(iType), buffer(256),doorid = GetPlayerDoorID(playerid)
			
			//dodaj akcesorium do domku
			format(buffer,sizeof(buffer),INSERT INTO hrp_doors_addons VALUES(NULL,%i,%i),DoorData(doorid)(dUID),addonType)
			mysql_query(buffer)
			
			DeleteItem(ItemInfo(addonID)(iUID))
			
			ReloadHomephones()
			
			GuiMsg(playerid,Zamontowałeś telefon stacjonarny w pomieszczeniu.,0)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DOOR_PHONE_MENU)
	(
		if(response)
		(
			phoneid = MainPlayerTable(playerid)
			
			string(128)
			if(strlen(inputtext) ) 7 || strlen(inputtext) (= 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Podany numer jest nieprawidłowy., OK, )
				return 1
			)

			number = strval(inputtext)

			if(HomePhones(phoneid)(hPhoneNumber) == number)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Podany numer jest nieprawidłowy., OK, )
				return 1	
			)

			callid = -1
			
			if(number ) 999999)
			(
				// Dzwoni do budki
				foreach(Phones, phone)
				(
					if(Phones(phone)(phoneNumber) == number)
					(
						callid = Itter_Free(Calls)
						
						Call(callid)(caller) = playerid
						
						Call(callid)(called) = INVALID_PLAYER_ID
						Call(callid)(calledNumber) = number
						Call(callid)(calledDevice) = DEVICE_BOX
						Call(callid)(calledDevID) = phone
						break
					)
				)
			)
			else if(number ) 999 && number ( 9999)
			(
				// Dzwoni na stacjonarny
				for(i = 0  i ( MAX_HOMEPHONES i++)
				(
					if(HomePhones(i)(hPhoneNumber) == number)
					(
						callid = Itter_Free(Calls)
						
						Call(callid)(caller) = playerid
						
						Call(callid)(called) = INVALID_PLAYER_ID
						Call(callid)(calledNumber) = number
						Call(callid)(calledDevice) = DEVICE_HOME
						Call(callid)(calledDevID) = i
						break
					)
				)
			)
			else if(number ) 99 && number (= 999)
			(
				PlayerCache(playerid)(pSerivceNumberAs) = HomePhones(phoneid)(hPhoneNumber)
				// Dzwoni na numer alarmowy/sklep/taxi/etc.
				if(number == 333)
				(
					doorid = GetPlayerDoorID(playerid)
					if(doorid == INVALID_DOOR_ID)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Aby skontaktować się z hurtownią, musisz znajdować się w budynku., OK, )
						return 1
					)
					if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie jesteś wlaścicielem tego budynku., OK, )
						return 1
					)
					if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
					(
						if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_ORDER))
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz odpowiednich uprawnień do zamawiania produktów., OK, )
							return 1
						)
					)
					MainPlayerTable(playerid) = doorid
					
					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)
					
					data(48), list_cat(512),
						cat_uid, cat_name(32)
					
					mysql_query(SELECT * FROM hrp_orders_cat)
					
					mysql_store_result()
					while(mysql_fetch_row(data, |))
					(
						sscanf(data, p(|)ds(32), cat_uid, cat_name)
						format(list_cat, sizeof(list_cat), %s\n%d\t%s, list_cat, cat_uid, cat_name)
					)
					mysql_free_result()
					if(strlen(list_cat))
					(
						ShowPlayerDialog(playerid, D_PRODUCT_TYPE, DIALOG_STYLE_LIST, Wybierz kategorię Ci odpowiadającą:, list_cat, Wybierz, Anuluj)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie znaleziono żadnych kategorii., OK, )
					)
					return 1
				)
				if(number == 777)
				(
					list_taxi_corp(1024)
					foreach(Groups, group_id_fix)
					(
						if(GroupData(group_id_fix)(gUID))
						(
							if(GroupData(group_id_fix)(gType) == GROUP_TAXI)
							(
								workers = 0
								foreach(Player, i)
								(
									if(Logged(i) && Spawned(i))
									(
										if(PlayerCache(i)(pGroupDuty) == GroupData(group_id_fix)(gUID))
										(
						 					workers ++
										)
									)
								)
								if(workers)
								(
									format(list_taxi_corp, sizeof(list_taxi_corp), %s\n%d\t(na służbie %d)\t%s, list_taxi_corp, group_id_fix, workers, GroupData(group_id_fix)(gName))
								)
							)
						)
					)
					if(strlen(list_taxi_corp))
					(
			  			//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
						//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
						attachPlayerPhone(playerid)
					
						ShowPlayerDialog(playerid, D_SELECT_TAXI_CORP, DIALOG_STYLE_LIST, Korporacje taksówkarskie, list_taxi_corp, Dalej, Anuluj)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, W chwili obecnej nie ma żadnej taksówki na służbie., OK, )
					)
					return 1
				)
				if(number == 911)
				(
					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)
					
					SendClientMessage(playerid, COLOR_YELLOW, Sekretarka: Witaj, połączyłeś się z numerem alarmowym centrali Los Santos, z kim połączyć?)
					ShowPlayerDialog(playerid, D_ALARM_NUMBER, DIALOG_STYLE_LIST, Z kim chcesz się połączyć?, Los Santos Police Department\nLos Santos Medical Center\nLos Santos Fire Department\nDepartment Of Sanitation Electricity, Wybierz, Anuluj)
					return 1
				)
				if(number == 444)
				(
					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)

					ShowPlayerDialog(playerid, D_SN_CALL, DIALOG_STYLE_INPUT, Los Santos News, Dodzwoniłeś się do radiostacji w Los Santos.\nPowiedz nam po krótce w czym rzecz., Dalej, Anuluj)
					return 1
				)
			)
			else if(number ) 99999 && number (= 999999)
			(
				// Dzwoni na komórkę
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pPhoneNumber) == number)
						(
							if(PlayerCache(i)(pCall) != -1)
							(
								SendClientMessage(playerid, COLOR_DO, ** Słychać sygnał zajętości... **)
							)
							else
							(
								callid = Itter_Free(Calls)
								Call(callid)(called) = i
								Call(callid)(calledNumber) = PlayerCache(i)(pPhoneNumber)
								Call(callid)(calledDevice) = DEVICE_CELL
							)
							break
						)
					)
				)
			)
			
			if(callid != -1)
			(
				if(HomePhones(phoneid)(hphoneBusy))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Błąd, Ktoś już używa tego telefonu., OK, )
					EndCall(callid)
					return 0
				)

				Call(callid)(caller) = playerid
				Call(callid)(callerNumber) = HomePhones(phoneid)(hPhoneNumber)
				Call(callid)(callerDevice) = DEVICE_HOME
				Call(callid)(callerDevID) = phoneid
				
				if(Call(callid)(calledDevice) == DEVICE_HOME)
				(
					foreach(Player, i)
					(
						if(CanPlayerHearHomephone(i, Call(callid)(calledDevID)))
						(
							SendClientMessage(i, COLOR_DO, ** Słychać dźwięk dzwoniącego telefonu domowego. **)
							PlayerPlaySound(i, 20600, 0.0, 0.0, 0.0)
						)
					)
				)

				if(Call(callid)(calledDevice) == DEVICE_BOX)
				(
					// Dzwonek budki dla wszystkich
					foreach(Player, i)
					(
						if(CanPlayerHearPhone(i, Call(callid)(calledDevID)))
						(
							SendClientMessage(i, COLOR_DO, ** Słyszysz dĽwięk telefonu w pobliżu. Brzmi jak budka telefoniczna. **)
							PlayerPlaySound(i, 20600, 0.0, 0.0, 0.0)
						)
					)

				)
				else if(Call(callid)(calledDevice) == DEVICE_CELL)
				(
					// Dzwonek komórki dla gracza
					format(string, sizeof(string), * Słychać dźwięk dzwoniącego telefonu. (( %s )), PlayerName(Call(callid)(called)))
					ProxDetector(10.0, Call(callid)(called), string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, false)

					// Audio dzwonka
					Float:PosX, Float:PosY, Float:PosZ
					GetPlayerPos(Call(callid)(called), PosX, PosY, PosZ)

					foreach(Player, player)
					(
						if(Logged(player) && Spawned(player))
						(
							if(IsPlayerInRangeOfPoint(player, 10.0, PosX, PosY, PosZ))
							(
								// Miejsce na dźwięk dzwonienia telefonu
								//audio = Audio_Play(player, AUDIO_CALLING)
								//Audio_Set3DPosition(player, audio, PosX, PosY, PosZ, 10.0)
							)
						)
					)
				)

				//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
				//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
				attachPlayerPhone(playerid)

				HomePhones(phoneid)(hphoneBusy) = true

				SendClientMessage(playerid, COLOR_DO, * Słychać sygnał próby połączenia się... *)

				format(string, sizeof(string), Połączenie przychodzące od %d, użyj /odbierz, by odebrać rozmowę., HomePhones(phoneid)(hPhoneNumber))
				SendClientMessage(Call(callid)(called), COLOR_YELLOW, string)
				
				PlayerCache(playerid)(pCall) = callid

				Itter_Add(Calls, callid)
				return 1
			)

			SendClientMessage(playerid, COLOR_DO, * Nie można połączyć się z wybranym numerem...)
			
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_VEH_ADDONS)
	(
		if(response)
		(
			vehicle = GetPlayerVehicleID(playerid)
			//dodaj możliwość wyciągania dodatków do EQ.
			//listitem
			buffer(256)
			format(buffer,sizeof(buffer),SELECT item_uid,item_name FROM hrp_items WHERE item_vehuid=%i AND item_type=%i,CarInfo(vehicle)(cUID),ITEM_TUNEPART)
			mysql_query(buffer)
			
			mysql_store_result()
			num = 0
			while(mysql_fetch_row(buffer,|))
			(
				if(num == listitem)
				(
					uid,name(32)
					sscanf(buffer,p(|)is(32),uid,name)
					MainPlayerTable(playerid) = uid
					
					msg(128)
					format(msg,sizeof(msg),Czy na pewno chcesz wyciągnąć %s z tego pojazdu?,name)
					
					ShowPlayerDialog(playerid,D_VEH_ADDON_DISMOUNT,DIALOG_STYLE_MSGBOX,Demontaż,msg,Tak,Nie)
					break
				)
				else
				(
					continue
				)
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_VEH_ADDON_DISMOUNT)
	(
		if(response)
		(
			//ItemInfo(itemid)(iOwner) = PlayerCache(playerid)(pUID)
			//ItemInfo(itemid)(iPlace) = PLACE_PLAYER
			
			itemUID = MainPlayerTable(playerid)
			buffer(256)
			format(buffer,sizeof(buffer),UPDATE hrp_items SET item_vehuid = 0 , item_place=%i, item_owner=%i WHERE item_uid=%i,PLACE_PLAYER,PlayerCache(playerid)(pUID),itemUID)
			mysql_query(buffer)
			
			LoadItem(itemUID)
			
			LoadVehicleTune(GetPlayerVehicleID(playerid))	
			
			GuiMsg(playerid,Wyciągnąłeś wskazane akcesorium z pojazdu.,0)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_WBC_PRESS)
	(
		if(response)
		(
			PlayerCache(playerid)(pRead) = false
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE )
			RemovePlayerAttachedObject(playerid,SLOT_PHONE)
		)
		else
		(
			PlayerCache(playerid)(pRead) = false
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE )
			RemovePlayerAttachedObject(playerid,SLOT_PHONE)
			return 1
		)
	)
	if(dialogid == D_WBC_CREATE)
	(
		if(response)
		(
			//tworz
			PlayerCache(playerid)(pPressStage) = 1
			ShowPlayerDialog(playerid,D_WBC_WRITE,DIALOG_STYLE_INPUT,Redakcja: akapit 1,Wprowadź poniżej treść pierwszego akapitu, maksymalnie można utworzyć osiem akapitów.,Gotowe,Anuluj)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_WBC_WRITE)
	(
		if(response)
		(
			if(PlayerCache(playerid)(pPressStage) ) 8)
			(
				ShowPlayerDialog(playerid,D_WBC_TITLE,DIALOG_STYLE_INPUT,Redakcja: finalizacja,Zakończ pisanie artykułu poprzez wpisanie jego tytułu.,Gotowe,Anuluj)
				return 1
			)
			
			switch(PlayerCache(playerid)(pPressStage))
			(
				case 1:
				(
					format(WBCpress,sizeof(WBCpress),%s,inputtext)
				)
				case 2..8:
				(
					if(strlen(inputtext) ) 1)
					(
						format(WBCpress,sizeof(WBCpress),%s\n%s,WBCpress,inputtext)
					)
				)
				case 9:
				(
					ShowPlayerDialog(playerid,D_WBC_TITLE,DIALOG_STYLE_INPUT,Redakcja: finalizacja,Zakończ pisanie artykułu poprzez wpisanie jego tytułu.,Gotowe,Anuluj)
				)
			)
			
			PlayerCache(playerid)(pPressStage)++
			
			title(32)
			format(title,sizeof(title),Redakcja %i/8,PlayerCache(playerid)(pPressStage))
			
			ShowPlayerDialog(playerid,D_WBC_WRITE,DIALOG_STYLE_INPUT,title,Wprowadź poniżej treść następnego akapitu.,Gotowe,Anuluj)
		)
		else
		(
			ShowPlayerDialog(playerid,D_WBC_TITLE,DIALOG_STYLE_INPUT,Redakcja: finalizacja,Zakończ pisanie artykułu poprzez wpisanie jego tytułu.,Gotowe,Anuluj)
		)
	)
	if(dialogid == D_WBC_TITLE)
	(
		if(response)
		(
			if(strlen(WBCpress) (= 1)
			(
				GuiMsg(playerid,Tekst, który utworzyłeś jest zdecydowanie za krótki by go opublikować.,0)
				return 1
			)
			
			toTitle(64)
			mysql_real_escape_string(inputtext, toTitle)
			
			PlayerCache(playerid)(pPressStage) = 0
			
			
			InsertNews(playerid,toTitle)
			
			GuiMsg(playerid,Zakończyłeś proces redagowania kolejnej części Los Santos Times.,0)
		)
		else
		(
			GuiMsg(playerid,Przerwałeś redagowanie kolejnego wydania Los Santos Times.,0)
			return 1
		)
	)
	if(dialogid == D_PRESS_BUY)
	(
		if(response)
		(
			if(PlayerCache(playerid)(pCash) ( 3)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, Nie posiadasz takiej ilości gotówki., OK, )
				return 1
			)
			
			buffer(256)
			
			for(i = 0  i ( MAX_PRESSBOX i++)
			(
				if(IsPlayerInRangeOfPoint(playerid,2.0,PressBox(i)(bPosX),PressBox(i)(bPosY),PressBox(i)(bPosZ)))
				(
					if(GetPlayerVirtualWorld(playerid) == PressBox(i)(bVW))
					(
						if(PressBox(i)(bAmount) ) 0)
						(
							//zmniejsz
							PressBox(i)(bAmount) = PressBox(i)(bAmount) - 1
							format(buffer,sizeof(buffer),UPDATE wbc_newsboxes SET box_amount = box_amount - 1 WHERE box_id=%i,PressBox(i)(bUID))
							mysql_query(buffer)
						)
					)
				)
			)
			
			hrp_GivePlayerMoney(playerid, -3)
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			format(buffer,sizeof(buffer),SELECT MAX(news_id) FROM wbc_press)
			mysql_query(buffer)
			mysql_store_result()
			last_newspaper = mysql_fetch_int()	
			mysql_free_result()
			
			CreatePlayerItem(playerid, Gazeta, 65, last_newspaper,0)
			
			group_id_fix = -1
			for(i = 0 i ( MAX_GROUPS i++)
			(
				if(GroupData(i)(gType) == GROUP_NEWS)
				(
					group_id_fix = i
					break
				)
				else
				(
					continue
				)
			)
			
			if(group_id_fix != -1)
			(
				GroupData(group_id_fix)(gCash) += 3
			)
			
			GuiMsg(playerid,Kupiłeś gazetę, powinna pojawić się w Twoim ekwipunku.,0)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_PRESS_JOB)
	(
		if(response)
		(
			if(!PlayerCache(playerid)(pSpread))
			(
				if( PlayerCache(playerid)(pSpreadTime) ) 0 )
				(
					GuiMsg(playerid,Musisz chwilę odczekać zanim rozwieziesz kolejną paczkę.,1)
					return 1
				)
				
				loss:
				
				box_id = random(sizeof(PressBox))
				if(PressBox(box_id)(bUID) (= 0)
				(
					goto loss
				)
				
				SetPlayerCheckpoint(playerid,PressBox(box_id)(bPosX),PressBox(box_id)(bPosY),PressBox(box_id)(bPosZ), 4.0)
				PlayerCache(playerid)(pSpread) = true
				PlayerCache(playerid)(pSpreadTime) = 60
				
				GuiMsg(playerid,Rozpocząłeś własnie rozwożenie gazet, udaj się do wskazanego punktu by dostarczyć gazety do pojemnika\n\nGdy dojedziesz na miejsce użyj komendy (FF0000)/gazety,0)
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_FBI_FAKEPAPERS)
	(
		if(response)
		(
			if(strlen(inputtext) (= 5)
			(
				GuiMsg(playerid, Niepoprawny nick., 1)
				return 1
			)
			
			new_name(MAX_PLAYER_NAME)
			format(new_name, sizeof(new_name), %s,inputtext)
			
			for(i = 0 i ( strlen(new_name) i++)
			(
				if(new_name(i) ==  ) new_name(i) = _
			)
			
			//dodaj do logów info o zmianie nicku
			log(256)
			format(log,sizeof(log),(info) (fakepapers) Gracz %s (UID: %i) zmienil swoj nick na %s ,PlayerName(playerid),PlayerCache(playerid)(pUID),new_name)
			print(log)
			
			strmid(PlayerCache(playerid)(pName), new_name, 0, strlen(new_name), MAX_PLAYER_NAME)
			PlayerCache(playerid)(pChangeName) = true
			
			SetPlayerName(playerid,new_name)
			
			GuiMsg(playerid,Zmieniłes swoje personalia.,1)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_DOOR_SET_TIME)
	(
		if(response)
		(
			hour = strval(inputtext)
			if(hour ) 24 || hour ( 0)
			(
				GuiMsg(playerid,Wprowadzono błędną godzinę, nie może być ona mniejsza od 0 i większa od 24,1)
				return 1
			)
			
			doorid = GetPlayerDoorID(playerid)
			if(doorid != INVALID_DOOR_ID)
			(
				buffer(256)
				format(buffer,sizeof(buffer),UPDATE hrp_doors SET door_time=%i WHERE door_uid=%i,hour,DoorData(doorid)(dUID))
				mysql_query(buffer)
				
				DoorData(doorid)(dTime) = hour
				
				for(i = 0  i ( MAX_PLAYERSi++)
				(
					if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
					(
						SetPlayerTime(i,DoorData(doorid)(dTime),0)
					)
				)
				
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_CREATE_CARD)
	(
		if(response)
		(
			limit = strval(inputtext)
			if(limit ( 0 || limit ) 10000)
			(
				GuiMsg(playerid,Maksymalna kwota to $10,000.,1)
				return 1
			)
			
			group_id_fix = GetPlayerDutyGroupID(playerid)
			if(group_id_fix == INVALID_GROUP_ID)
			(
				GuiMsg(playerid, Musisz być na duty grupy, którą chcesz wydać kartę.,1)
				return 1
			)

			if(!IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_LEADER))
			(
				GuiMsg(playerid, Nie jesteś liderem tej grupy!,1)
				return 1
			)

			cardid = CreateCard(GroupData(group_id_fix)(gUID), limit)
			itemid = MainPlayerTable(playerid)
			ItemInfo(itemid)(iValue1) = cardid

			mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
			GuiMsg(playerid, Twoja karta została poprawnie stworzona, 1)

			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	if(dialogid == D_SELECT_CHAR)
	(
		if(response)
		(
			buffer(256)
			format(buffer,sizeof(buffer),SELECT char_uid, char_name FROM hrp_characters WHERE char_gid=%i,PlayerCache(playerid)(pGID))
			mysql_query(buffer)
			mysql_store_result()
			
			charUID,charName(32),num = 0
			while(mysql_fetch_row(buffer,|))
			(
				if(num == listitem)
				(
					sscanf(buffer,p(|)ds(32),charUID,charName)
					break
				)
				num++
			)
			
			mysql_free_result()
			
			if(!strcmp(charName, PlayerCache(playerid)(pName), true))
			(
				GuiMsg(playerid,Przecież wlaśnie jesteś zalogowany na tej postaci.,1)
				return 1
			)
			
			string(256)
			format(string,sizeof(string),(( Gracz %s przełącza się właśnie między postaciami )),PlayerName(playerid))
			ProxDetector(50, playerid, string, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true)
			
			GuiMsg(playerid,Poczekaj chwilę, proces przejścia między postacią trwa chwilę...,0)
			SetPlayerName(playerid,charName)
			SetTimerEx(SetPlayerToChangeChar,100,false,i,playerid)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_MANDAT_PD_INPUT_NAME)
	(
		if(response)
		(
			checkedid = INVALID_PLAYER_ID
			for(i = 0 i (MAX_PLAYERS i++)
			(
				pname(MAX_PLAYER_NAME)
				GetPlayerName(i,pname,sizeof(pname))
				
				if(!strcmp(pname, PlayerCache(i)(pName), true))
				(
					checkedid = i
					break
				)
			)
			
			if(checkedid == INVALID_PLAYER_ID)
			(
				GuiMsg(playerid,Brak wyników dla podanych personaliów.,1)
				return 1
			)
			
			ShowPlayerDirectoryForPlayer(playerid, checkedid)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_INTERFACE_SELECT)
	(
		if(response)
		(
			buffer(256)
			switch(listitem)
			(
				case 0:	//text
				(
					format(buffer,sizeof(buffer),UPDATE hrp_characters SET char_interface = %i WHERE char_uid = %i,INTERFACE_TYPE_TEXT,PlayerCache(playerid)(pUID))
					PlayerCache(playerid)(pInterface) = INTERFACE_TYPE_TEXT
				)
				case 1:	//gui
				(
					format(buffer,sizeof(buffer),UPDATE hrp_characters SET char_interface = %i WHERE char_uid = %i,INTERFACE_TYPE_GRAPHIC,PlayerCache(playerid)(pUID))
					PlayerCache(playerid)(pInterface) = INTERFACE_TYPE_GRAPHIC
				)
			)
			
			mysql_query(buffer)
			
			if(PlayerCache(playerid)(pInterface) == INTERFACE_TYPE_GRAPHIC)
			(
				GuiMsg(playerid,Zmieniłeś typ swojego interfejsu na graficzny.,0)
			)
			else
			(
				GuiMsg(playerid,Zmieniłeś typ swojego interfejsu na tekstowy.,0)
			)
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_ZONE_MENU)
	(
		if(GetPlayerZoneID(playerid) == INVALID_ZONE_ID)
		(
			return 1
		)
		if(response)
		(
			// Check to make sure you cant spook being an owner by moving with the window open in another area.
			zone = GetPlayerZoneID(playerid)
			if(!IsPlayerInGroup(playerid, ZoneInfo(zone)(zOwner)))
			(
				GuiMsg(playerid, Nie jesteś członkiem organizacji, do której należy ten teren., 1)
				return 1
			)
			if(!IsPlayerPermissedGroup(playerid, ZoneInfo(zone)(zOwner), PERM_LEADER))
			(
				GuiMsg(playerid, Musisz posiadać uprawnienia lidera, by móc zarządzać terenem., 1)
				return 1
			)
			if(ZoneInfo(zone)(zType) == ZONE_TYPE_MAIN)
			(
				GuiMsg(playerid, Nie możesz zarządzać strefą, która jest sercem Twojej organizacji., 1)
				return 1
			)

			switch(listitem)
			(
				case 0:
				(
					//informacje
					zoneid = GetPlayerZoneID(playerid)
					GetZoneInfo(playerid, zoneid)
				)
				case 1:
				(
					//oddaj
					if(Logged(playerid))
					(
						GuiMsg(playerid, Funkcja tymczasowo zablokowana., 1)
						return 1
					)
					
					personList(256)
					Float:PosX, Float:PosY, Float:PosZ
					GetPlayerPos(playerid, PosX, PosY, PosZ)
					
					for(i = 0  i ( MAX_PLAYERS i++)
					(
						if(playerid == i)
						(
							continue
						)
						if(IsPlayerInRangeOfPoint(i,5.0, PosX, PosY, PosZ))
						(
							if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
							(
								if(IsPlayerInGroupType(i, GROUP_CRIMINAL))
								(
									format(personList, sizeof(personList), %s\n%i\t\t%s, personList, i, PlayerName(i))
								)
							)
						)
					)
					
					if(!strlen(personList))
					(
						GuiMsg(playerid, Nie znaleziono żadnej pasującej osoby w pobliżu., 1)
					)
					else
					(
						ShowPlayerDialog(playerid, D_ZONE_OFFER, DIALOG_STYLE_LIST, Oddaj strefę, personList, Wybierz, Anuluj)
					)
				)
				// Jesli to odkomentowuejsz to pamietaj o zmianie numeracji i zmianie wszystkich wywolan D_ZONE_MENU
				/*case 2:
				(
					//opusc
					zoneid = GetPlayerZoneID(playerid)
					ZoneInfo(zoneid)(zOwner) = 0
					ZoneInfo(zoneid)(zType) = 0
					
					GuiMsg(playerid, Twoja organizacja opuściła teren, na którym aktualnie jesteś., 1)
					
					ReloadZones() // na koniec
				)*/
				case 2:
				(
					//bonus
					zoneid = GetPlayerZoneID(playerid)
					if(!ZoneInfo(zoneid)(zPackage))
					(
						GuiMsg(playerid, Odebrano już paczkę z tej strefy., 1)
						return 1
					)
					
					switch(ZoneInfo(zoneid)(zType))
					(
						case ZONE_TYPE_NONE:
						(
							GuiMsg(playerid, Ten teren nie posiada żadnego bonusa., 1)
							return 1
						)
						case ZONE_TYPE_MONEY:
						(
							loss:
							rand = random(300)
							if(rand ( 150)
							(
								goto loss
							)
							
							GuiMsg(playerid, Odpakowałeś paczkę, wewnątrz znajduje się trochę kasy., 1)
							
							hrp_GivePlayerMoney(playerid, rand)
							ZoneInfo(zoneid)(zPackage) = false
						)
						case ZONE_TYPE_GUN:
						(
							randType = random(100)
							type = 0
							if(randType ( 30)
							(
								type = 1
							)
							else
							(
								type = 2
							)
							
							bool:isEmpty = false
							
							switch(type)
							(
								case 1:
								(
									randAmmo = random(100)
									switch(randAmmo)
									(
										case 0..19:
										(
											CreatePlayerItem(playerid, Amunicja 9mm, 7, 22, 34)
										)
										case 20..23:
										(
											CreatePlayerItem(playerid, Amunicja AK-47, 7, 30, 60)
										)
										case 24..34:
										(
											CreatePlayerItem(playerid, Amunicja Tec-9, 7, 32, 60)
										)
										case 35..44:
										(
											CreatePlayerItem(playerid, Amunicja Uzi, 7, 28, 60)
										)
										case 45..54:
										(
											CreatePlayerItem(playerid, Amunicja Obrzyn, 7, 26, 12)
										)
										case 55..56:
										(
											CreatePlayerItem(playerid, Tłumik, 74, 0, 0)
										)
										case 57..65:
										(
											CreatePlayerItem(playerid, Amunicja Strzelba, 7, 25, 15)
										)
										case 66..100:
										(
											isEmpty = true
										)
									)
								)
								
								case 2:
								(
									randGun = random(100)
									switch(randGun)
									(
										case 0..19:
										(
											CreatePlayerItem(playerid, 9mm, 6, 22, 34)
										)
										case 20..23:
										(
											CreatePlayerItem(playerid, AK-47, 6, 30, 60)
										)
										case 24..34:
										(
											CreatePlayerItem(playerid, Tec-9, 6, 32, 60)
										)
										case 35..44:
										(
											CreatePlayerItem(playerid, Uzi, 6, 28, 60)
										)
										case 45..54:
										(
											CreatePlayerItem(playerid, Obrzyn, 6, 26, 12)
										)
										case 55..56:
										(
											CreatePlayerItem(playerid, Tłumik, 74, 0, 0)
										)
										case 57..65:
										(
											CreatePlayerItem(playerid, Strzelba, 6, 25, 15)
										)
										case 66..100:
										(
											isEmpty = true
										)
									)
								)
							)
							
							if(!isEmpty)
							(
								GuiMsg(playerid, Odpakowałeś paczkę, wewnątrz znalazłeś broń.\nTeraz znajduje się w Twoim ekwipunku., 0)
							)
							else
							(
								GuiMsg(playerid, Odpakowałeś paczkę, okazało się, że jest pusta!, 0)
							)
							
							ZoneInfo(zoneid)(zPackage) = false
						)
						case ZONE_TYPE_DRUG:
						(
							rand = random(100)
							switch(rand)
							(
								case 0..14:		// marycha 2
								(
									CreatePlayerItem(playerid, Dobra marihuana (2g),25,1,2)
								)
								case 15..29:		// marycha 4
								(
									CreatePlayerItem(playerid, Uliczna marihuana (4g),25,1,4)
								)
								case 30.. 34:		// kokaina 2
								(
									CreatePlayerItem(playerid, Uliczna kokaina (2g),25,2,2)
								)
								case 35..45:		// heroina 2
								(
									CreatePlayerItem(playerid, Czysta heroina (2g),25,3,2)
								)
								case 46..51:		// heroina 4
								(
									CreatePlayerItem(playerid, Brązowa heroina (4g),25,3,4)
								)
								case 52..63:		//amfetamina 2g
								(
									CreatePlayerItem(playerid, Czysta amfetamina (2g),25,4,2)
								)
								case 64..76:		// crack 2g
								(
									CreatePlayerItem(playerid, Uliczny crack (2g),25,6,2)
								)
								case 77..94:		//crack 4g
								(
									CreatePlayerItem(playerid, Zanieczyszczony crack (4g),25,6,4)
								)
								case 95..99:	// amfetamina 4g
								(
									CreatePlayerItem(playerid, Uliczna amfetamina (4g),25,4,4)
								)
							)
						
							GuiMsg(playerid, Otworzyłeś paczkę, wewnątrz było trochę narkotyku.\nPojawił się on w Twoim ekwipunku., 1)
							ZoneInfo(zoneid)(zPackage) = false
						)
						case ZONE_TYPE_MAIN:
						(
							GuiMsg(playerid, Ten teren nie generuje żadnych paczek., 1)
							return 1
						)
					)
				)
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ZONE_OFFER)
	(
		if(response)
		(
			Float:PosX, Float:PosY, Float:PosZ
			GetPlayerPos(playerid, PosX, PosY, PosZ)
			
			offeredto = -1, loops = 0
			for(i = 0  i ( MAX_PLAYERS i++)
			(
				if(playerid == i)
					continue
				
				if(GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid))
					continue
				
				if(!IsPlayerInGroupType(i, GROUP_CRIMINAL))
					continue
				
				if(!IsPlayerInRangeOfPoint(i, 5.0, PosX, PosY, PosZ))
					continue
					
				if(loops == listitem)
				(
					offeredto = i
					break
				)
				
				loops++
			)
			
			if(Logged(offeredto) && Spawned(offeredto))
			(
				MainPlayerTable(playerid) = offeredto
				MainPlayerTable(offeredto) = playerid
				
				message(128)
				format(message, sizeof(message), Zaoferowałeś graczowi %s strefę, na której aktualnie jesteś, poczekaj na jego odpowiedź., PlayerName(offeredto))
				SendClientMessage(playerid, COLOR_KREM, message)
				
				format(message, sizeof(message), Gracz %s zaoferował Ci teren na którym teraz stoisz, czy chcesz go przejąć?, PlayerName(playerid))
				ShowPlayerDialog(offeredto, D_ZONE_GIVE, DIALOG_STYLE_MSGBOX, Oferta, message, Tak, Nie)
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_ZONE_GIVE)
	(
		offerer = MainPlayerTable(playerid)
		zoneid = GetPlayerZoneID(playerid)
		if(response)
		(
			message(128)
			format(message, sizeof(message), Gracz %s akceptował ofertę przejęcia terenu., PlayerName(playerid))
			SendClientMessage(offerer, COLOR_KREM, message)
			
			GuiMsg(playerid, Akceptowałeś ofertę, od teraz dzielnica należy do Ciebie., 0)
			
			group_id_fix, gSlot = 0
			for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
			(
				if(PlayerGroup(playerid)(slot)(gUID))
				(
					group_id_fix = PlayerGroup(playerid)(slot)(gID)
					if(GroupData(group_id_fix)(gType) == GROUP_CRIMINAL)
					(
						gSlot = slot
						break
					)
				)
			)
			
			ZoneInfo(zoneid)(zOwner) = PlayerGroup(playerid)(gSlot)(gUID)
			
			ReloadZones() // na koniec
		)
		else
		(
			message(128)
			format(message, sizeof(message), Gracz %s odrzucił ofertę przejęcia terenu., PlayerName(playerid))
			
			SendClientMessage(offerer, COLOR_KREM, message)
			GuiMsg(playerid, Odrzuciłeś ofertę., 0)
			return 1
		)
	)
	if(dialogid == D_WEAPON_SILENCER_SELECT)
	(
		if(response)
		(
			item_uid = strval(inputtext), item_id = GetItemID(item_uid)
			
			if(ItemInfo(item_id)(iUsed))
			(
				GuiMsg(playerid, Nie możesz założyć tłumika podczas, gdy używasz tej broni., 1)
				return 1
			)
			
			if(!strfind(ItemInfo(item_id)(iName), (F), true))
			(
				CreatePlayerItem(playerid, (F) Pistolet z tlumikiem, 6, 23, ItemInfo(item_id)(iValue2))
			)
			else if(!strfind(ItemInfo(item_id)(iName), (G), true))
			(
				CreatePlayerItem(playerid, (G) Pistolet z tlumikiem, 6, 23, ItemInfo(item_id)(iValue2))
			)
			else if(!strfind(ItemInfo(item_id)(iName), (H), true))
			(
				CreatePlayerItem(playerid, (H) Pistolet z tlumikiem, 6, 23, ItemInfo(item_id)(iValue2))
			)
			else
			(
				CreatePlayerItem(playerid, Pistolet z tlumikiem, 6, 23, ItemInfo(item_id)(iValue2))
			)
			
			//CreatePlayerItem(playerid, Pistolet z tlumikiem, 6, 23, ItemInfo(item_id)(iValue2))
			DeleteItem(item_uid)
			
			foreach(Items, i)
			(
				if(ItemInfo(i)(iUID))
				(
					if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(ItemInfo(i)(iType) == ITEM_SILENCER)
						(
							DeleteItem(ItemInfo(i)(iUID))
							break
						)
					)
				)
			)
			
			GuiMsg(playerid, Założyłeś tłumik na wskazaną broń., 0)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_WEAPON_SILENCER_UNMOUNT)
	(
		if(response)
		(
			item_uid = strval(inputtext), item_id = GetItemID(item_uid)
			
			if(ItemInfo(item_id)(iUsed))
			(
				GuiMsg(playerid, Nie możesz zdjąć tłumika z używanej broni., 1)
				return 1
			)
			
			if(!strfind(ItemInfo(item_id)(iName), (F), true))
			(
				CreatePlayerItem(playerid, (F) Pistolet, ITEM_WEAPON, 22, ItemInfo(item_id)(iValue2))
				CreatePlayerItem(playerid, Tłumik, ITEM_SILENCER, 0, 0)
			)
			else if(!strfind(ItemInfo(item_id)(iName), (G), true))
			(
				CreatePlayerItem(playerid, (G) Pistolet, ITEM_WEAPON, 22, ItemInfo(item_id)(iValue2))
				CreatePlayerItem(playerid, Tłumik, ITEM_SILENCER, 0, 0)
			)
			else if(!strfind(ItemInfo(item_id)(iName), (H), true))
			(
				CreatePlayerItem(playerid, (H) Pistolet, ITEM_WEAPON, 22, ItemInfo(item_id)(iValue2))
				CreatePlayerItem(playerid, Tłumik, ITEM_SILENCER, 0, 0)
			)
			else
			(
				CreatePlayerItem(playerid, Pistolet, ITEM_WEAPON, 22, ItemInfo(item_id)(iValue2))
				CreatePlayerItem(playerid, Tłumik, ITEM_SILENCER, 0, 0)
			)
			
			//CreatePlayerItem(playerid, Pistolet, ITEM_WEAPON, 22, ItemInfo(item_id)(iValue2))
			//CreatePlayerItem(playerid, Tłumik, ITEM_SILENCER, 0, 0)
			DeleteItem(item_uid)
			
			GuiMsg(playerid, Zdjąłeś tłumik ze wskazanej broni., 0)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TEXT_MATSIZE)
	(
		if(response)
		(
			matsize = 0
			switch(listitem)
			(
				case 0:
					matsize = OBJECT_MATERIAL_SIZE_32x32
				case 1:
					matsize = OBJECT_MATERIAL_SIZE_64x32
				case 2:
					matsize = OBJECT_MATERIAL_SIZE_64x64
				case 3:
					matsize = OBJECT_MATERIAL_SIZE_128x32
				case 4:
					matsize = OBJECT_MATERIAL_SIZE_128x64
				case 5:
					matsize = OBJECT_MATERIAL_SIZE_128x128
				case 6:
					matsize = OBJECT_MATERIAL_SIZE_256x32
				case 7:
					matsize = OBJECT_MATERIAL_SIZE_256x64
				case 8:
					matsize = OBJECT_MATERIAL_SIZE_256x128
				case 9:
					matsize = OBJECT_MATERIAL_SIZE_256x256
				case 10:
					matsize = OBJECT_MATERIAL_SIZE_512x64
				case 11:
					matsize = OBJECT_MATERIAL_SIZE_512x128
				case 12:
					matsize = OBJECT_MATERIAL_SIZE_512x256
				case 13:
					matsize = OBJECT_MATERIAL_SIZE_512x512
			)
			
			PlayerCache(playerid)(pEMatSize) = matsize
			ShowPlayerDialog(playerid, D_TEXT_FONTFACE, DIALOG_STYLE_LIST, Wybierz czcionkę, 1. Arial\n2. Tahoma\n3. Times New Roman\n4. Diploma\n5. Beckett\n6. Impact, Wybierz, Anuluj)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TEXT_FONTFACE)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					format(PlayerCache(playerid)(pEMatFont), 32, Arial)
				)
				case 1:
				(
					format(PlayerCache(playerid)(pEMatFont), 32, Tahoma)
				)
				case 2:
				(
					format(PlayerCache(playerid)(pEMatFont), 32, Times New Roman)
				)
				case 3:
				(
					format(PlayerCache(playerid)(pEMatFont), 32, Diploma)
				)
				case 4:
				(
					format(PlayerCache(playerid)(pEMatFont), 32, Beckett)
				)
				case 5:
				(
					format(PlayerCache(playerid)(pEMatFont), 32, Impact)
				)
			)
			
			ShowPlayerDialog(playerid, D_TEXT_BOLD, DIALOG_STYLE_LIST, Pogrubienie, 1. Tak\n2. Nie, Wybierz, Anuluj)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TEXT_BOLD)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					PlayerCache(playerid)(pEMatBold) = 1
				)
				case 1:
				(
					PlayerCache(playerid)(pEMatBold) = 0
				)
			)
			
			// dialog
			ShowPlayerDialog(playerid, D_TEXT_FONTSIZE, DIALOG_STYLE_LIST, Wielkość tekstu, 12 px\n18 px\n24px\n32 px\n40 px\n50 px\n55 px\n62 px\n67 px\n72 px, Wybierz, Anuluj)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TEXT_FONTSIZE)
	(
		if(response)
		(
			textsize = strval(inputtext)
			PlayerCache(playerid)(pEMatFontSize) = textsize
			//dialog
			ShowPlayerDialog(playerid, D_TEXT_TEXT, DIALOG_STYLE_INPUT, Wpisz tekst, Poniżej wprowadź ciąg znaków, który ma się pojawić na edytowanym obiekcie., Gotowe, Anuluj)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_TEXT_TEXT)
	(
		if(response)
		(
			// Sprawdzenie tekstu - bo crashe
			if(strlen(inputtext) ) 32)
			(
				GuiMsg(playerid, Wprowadzony ciąg znaków jest za długi!, 1)
				return 1
			)
			
			objectid = PlayerCache(playerid)(pMoveObject)
			object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID)
			SetDynamicObjectMaterialText(objectid, 0, inputtext, PlayerCache(playerid)(pEMatSize), PlayerCache(playerid)(pEMatFont), PlayerCache(playerid)(pEMatFontSize), PlayerCache(playerid)(pEMatBold), 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER)
			
			// dodaj escape
			insertText(128)
			mysql_real_escape_string(inputtext, insertText)
			
			buffer(256)
			format(buffer, sizeof(buffer), SELECT * FROM hrp_materialtexts WHERE text_object = %d, object_uid)
			mysql_query(buffer)
			mysql_store_result()
			if(mysql_num_rows() ) 0)
			(
				mysql_free_result()
				mysql_query_format(UPDATE hrp_materialtexts SET text_matsize = %d, text_font = %s, text_fontsize = %d, text_text = %s, text_bold = %d WHERE text_object = %d, 
				PlayerCache(playerid)(pEMatSize), 
				PlayerCache(playerid)(pEMatFont),
				PlayerCache(playerid)(pEMatFontSize),
				insertText,
				PlayerCache(playerid)(pEMatBold),
				object_uid)
				
			)
			else
			(
				mysql_free_result()
				mysql_query_format(INSERT INTO hrp_materialtexts VALUES(NULL, %d, %s, %d, %s, %d, %d),
				PlayerCache(playerid)(pEMatSize), 
				PlayerCache(playerid)(pEMatFont),
				PlayerCache(playerid)(pEMatFontSize),
				insertText,
				PlayerCache(playerid)(pEMatBold),
				object_uid)
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_FISH_INFO)
	(
		if(response)
		(
			itemlist(512), itemcount = 0
			
			foreach(Items, i)
			(
				if(ItemInfo(i)(iUID))
				(
					if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(ItemInfo(i)(iType) != ITEM_FOOD)
							continue
						
						if(!strcmp(ItemInfo(i)(iName), Sledz, true) || !strcmp(ItemInfo(i)(iName), Sardynka, true) || !strcmp(ItemInfo(i)(iName), Tunczyk, true) || !strcmp(ItemInfo(i)(iName), Szczupak, true) || !strcmp(ItemInfo(i)(iName), Karas, true))
						(
							itemcount++
							format(itemlist, sizeof(itemlist), %s\n%d. %s, itemlist, ItemInfo(i)(iUID), ItemInfo(i)(iName))
						)
					)
				)
			)
			
			if(itemcount == 0)
			(
				GuiMsg(playerid, Nie posiadasz żadnej ryby w swoim ekwipunku., 1)
				return 1
			)
			
			ShowPlayerDialog(playerid, D_FISH_MARKET, DIALOG_STYLE_LIST, Handlarz » sprzedaj, itemlist, Wybierz, Anuluj)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_FISH_MARKET)
	(
		if(response)
		(
			fish_uid = strval(inputtext), fish_price = 0, safetyUID = PlayerCache(playerid)(pUID)
			switch(ItemInfo(GetItemID(fish_uid))(iValue1))
			(
				case 45:
					fish_price = 45
				case 25:
					fish_price = 25
				case 30:
					fish_price = 35
				case 50:
					fish_price = 65
			)
			
			msg(128)
			format(msg, sizeof(msg), Sprzedałes rybę!\nZarobiłeś właśnie $%d, brawo., fish_price)
			GuiMsg(playerid, msg, 0)
			
			DeleteItem(fish_uid)
			
			hrp_GivePlayerMoney(playerid, fish_price)
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			blint_SaveCash(safetyUID, playerid)
			hrp_MoneyActionLog(%s (UID: %d) zarobil $%d przy sprzedazy ryby., PlayerRealName(playerid), PlayerCache(playerid)(pUID), fish_price)
		
			PlayerCache(playerid)(pDailyIncome) += fish_price
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_SELECT_SCOURER)
	(
		if(response)
		(
			PlayerCache(playerid)(pJob) = JOB_SCOURER
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przyjąłeś pracę dorywczą czyściciela tagów, używaj komendy /czysc, OK, )
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_HALL)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					// podejdź do egzaminu
					if(!(PlayerCache(playerid)(pDocuments) & DOC_DRIVER))
					(
						ShowPlayerDialog(playerid, D_HALL_START_RIDE, DIALOG_STYLE_MSGBOX, Urząd » start egzaminu, Właśnie chcesz rozpocząć kurs prawa jazdy, polega on na przejechaniu trasy.\nKoszt egzaminu wynosi $400., Akceptuj, Zamknij)
					)
					else
					(
						GuiMsg(playerid, Posiadasz już ten dokument., 1)
					)
				)
				case 1:
				(
					// wyrób dowód
					// prawko tylko rzecz jasna
					ShowPlayerDialog(playerid, D_HALL_REGISTER, DIALOG_STYLE_INPUT, Urząd » rejestracja, Wpisz poniżej ID pojazdu, który chcesz zarejestrować.\nPamiętaj, że wartość nie może być mniejsza od 1 ani większa od 1000.\nWejdź do pojazdu i wpisz /v info by zobaczyć jego ID.\n\n, Gotowe, Anuluj)
				)
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_HALL_REGISTER)
	(
		if(response)
		(
			vehID = strval(inputtext)
			if(vehID ( 1 || vehID ) 1000)
			(
				GuiMsg(playerid, Wprowadzono błędne ID pojazdu., 1)
				return 1
			)
			
			if(PlayerCache(playerid)(pCash) ( 150)
			(
				GuiMsg(playerid, Nie posiadasz wystarczającej ilości gotówki., 1)
				return 1
			)
			
			if(GetVehicleModel(vehID) == 0)
			(
				GuiMsg(playerid, Taki pojazd nie istnieje., 1)
				return 1
			)
			
			if(CarInfo(vehID)(cRegister))
			(
				GuiMsg(playerid, Ten pojazd jest już zarejestrowany., 1)
				return 1
			)
			
			if(CarInfo(vehID)(cOwnerType) == OWNER_PLAYER && CarInfo(vehID)(cOwner) != PlayerCache(playerid)(pUID))
			(
				GuiMsg(playerid, Ten pojazd nie należy do Ciebie., 1)
				return 1
			)
			
			if(CarInfo(vehID)(cOwnerType) == OWNER_GROUP)
			(
				owner_group = CarInfo(vehID)(cOwner)
//				group_id_fix = GetGroupID(owner_group)
				
				if(!IsPlayerInGroup(playerid, owner_group))
				(
					GuiMsg(playerid, Ten pojazd nie należy do Ciebie., 1)
					return 1
				)
				
				if(!IsPlayerPermissedGroup(playerid, owner_group, PERM_CARS))
				(
					GuiMsg(playerid, Nie masz uprawnień do kontroli nad pojazdami w swojej grupie., 1)
					return 1
				)
			)
			
			CarInfo(vehID)(cRegister) = true
			SaveVehicle(vehID, SAVE_VEH_THINGS)
			
			string(32)
			format(string, sizeof(string), LS%d, CarInfo(vehID)(cUID))
			SetVehicleNumberPlate(vehID, string)
			
			safeUID = PlayerCache(playerid)(pUID)
			hrp_GivePlayerMoney(playerid, -150)
			
			blint_SaveCash(safeUID, playerid)
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			GuiMsg(playerid, Pojazd został zarejestrowany, od teraz posiada tablice rejestracyjne!, 0)
			
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_HALL_START_RIDE)
	(
		if(response)
		(
			if(PlayerCache(playerid)(pCash) )= 400)
			(
				safeUID = PlayerCache(playerid)(pUID)
				hrp_GivePlayerMoney(playerid, -400)
				
				blint_SaveCash(safeUID, playerid)
				SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
				
				GuiMsg(playerid, Wykupiłeś właśnie kurs, wyjdź na zewnątrz i wsiądź do urzędowego auta.\nTam otrzymasz kolejne instrukcje., 0)
				
				PlayerCache(playerid)(pCourse) = true
				PlayerCache(playerid)(pCourseMS) = 0.0
				PlayerCache(playerid)(pCourseVeh) = INVALID_VEHICLE_ID
				PlayerCache(playerid)(pCourseCP) = 0
			)
			else
			(
				GuiMsg(playerid, Nie posiadasz tyle gotówki!, 1)
				return 1
			)
		)
		else
		(
			return 1
		)
	)
	if(dialogid == D_BUY_HOUSE)
	(
		if(response)
		(
			doorid = MainPlayerTable(playerid)
			MainPlayerTable(playerid) = 0
			safety = PlayerCache(playerid)(pUID)
			
			if(DoorData(doorid)(dOwnerType) != OWNER_NONE)
			(
				GuiMsg(playerid, Wystąpił błąd, użyj komendy jeszcze raz., 1)
				return 1
			)
			
			hrp_GivePlayerMoney(playerid, -DoorData(doorid)(dCost))
			blint_SaveCash(safety, playerid)	
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			DoorData(doorid)(dCost) = 0
			DoorData(doorid)(dOwnerType) = OWNER_PLAYER
			DoorData(doorid)(dOwner) = safety
			DoorData(doorid)(dPickupID) = 1273
			
			DestroyPickup(doorid)
			CreatePickup(DoorData(doorid)(dPickupID), 2, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), DoorData(doorid)(dEnterVW))
			mysql_query_format(UPDATE hrp_door_defaults SET default_checktime = %d WHERE default_dooruid = %d, gettime() + 2592000, DoorData(doorid)(dUID))
			
			SaveDoor(doorid, SAVE_DOOR_THINGS)

			PlayerTextDrawShow(playerid, TextDrawPropertyFade1(playerid))
			PlayerTextDrawShow(playerid, TextDrawPropertyFade2(playerid))
			PlayerTextDrawShow(playerid, TextDrawPropertyMSG(playerid))
			
			//SetPlayerPos(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ))
			//SetPlayerFacingAngle(playerid, DoorData(doorid)(dEnterAng) + 180.0)
			
			hrp_TogglePlayerControllable(playerid, 0)
			PlayerCache(playerid)(pBuyCount) = 10
			
			// ---------------------------------------------
			// -----        mały eksperyment         -----
			// ---------------------------------------------
			Float:doorEnterX, Float:doorEnterY, Float:doorEnterZ, Float:doorAngle
			doorEnterX = DoorData(doorid)(dEnterX)
			doorEnterY = DoorData(doorid)(dEnterY)
			doorEnterZ = DoorData(doorid)(dEnterZ)
			doorAngle = DoorData(doorid)(dEnterAng)

			GetXYInFrontOfPoint(doorEnterX, doorEnterY, doorAngle, 30.0)
			
			// ----------------------------------------------
			
			Float:doorCamX, Float:doorCamY, Float:doorCamZ, Float:doorCamAng
			doorCamX = DoorData(doorid)(dEnterX)
			doorCamY = DoorData(doorid)(dEnterY)
			doorCamZ = DoorData(doorid)(dEnterZ)
			doorCamAng = DoorData(doorid)(dEnterAng)
			
			GetXYInFrontOfPoint(doorCamX, doorCamY, doorCamAng, 5.0)
			SetPlayerCameraLookAt(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ))
			SetPlayerCameraPos(playerid, doorCamX, doorCamY, doorCamZ + 1.0)
			// ----------------------------------------------
			
			PlayAudioStreamForPlayer(playerid, http://lspd.xaa.pl/buyhouse.mp3)
			InterpolateCameraLookAt(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ),DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 10000, CAMERA_MOVE)
			InterpolateCameraPos(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), doorEnterX, doorEnterY, doorEnterZ + 3.0, 10000, CAMERA_MOVE)
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_BANDAGE)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					// Lecz siebie
					
					if(PlayerCache(playerid)(pBleeding) (= 0)
					(
						GuiMsg(playerid, Twoja postać nie krwawi, nie potrzebujesz używać tego przedmiotu., 1)
						return 1
					)
					
					if(PlayerCache(playerid)(pStrength) ( 30.0)
					(
						GuiMsg(playerid, Jesteś za słaby, by samodzielnie się opatrzeć., 1)
						return 1
					)
					
					// Startuj 
					string(256), Float:health GetPlayerHealth(playerid, health)
					format(string, sizeof(string), * %s owija postrzelone miejsce bandażem., PlayerName(playerid))
					
					if(health ) 50.0)
						PlayerCache(playerid)(pBleeding) = 0
					
					DeleteItem(ItemInfo(MainPlayerTable(playerid))(iUID))
					MainPlayerTable(playerid) = 0

					SendClientMessage(playerid, COLOR_DO, ** Opatrzyłeś się. **)
					FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
				)
				case 1:
				(
					// Lecz kogoś
					list_players(512), Float:Pos(3)
					GetPlayerPos(playerid, Pos(0), Pos(1), Pos(2))
					
					for(i = 0  i ( MAX_PLAYERS i++)
					(
						if(!IsPlayerConnected(i))
							continue
							
						if(GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid))
							continue
							
						if(PlayerCache(i)(pBleeding) (= 0)
							continue
							
						if(IsPlayerInRangeOfPoint(i, 5.0, Pos(0), Pos(1), Pos(2)))
						(
							format(list_players, sizeof(list_players), %s\n%d. \t\t%s, list_players, i, PlayerName(i))
						)
					)
					
					if(!strlen(list_players))
					(
						GuiMsg(playerid, W pobliżu nie ma żadnego rannego gracza., 1)
						return 1
					)
					
					ShowPlayerDialog(playerid, D_BANDAGE_SOMEONE, DIALOG_STYLE_LIST, Lista graczy, list_players, Wybierz, Anuluj)
				)
			)
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	
	if(dialogid == D_BANDAGE_SOMEONE)
	(
		if(response)
		(
			selected_id = strval(inputtext)
			if(!IsPlayerConnected(selected_id))
			(
				GuiMsg(playerid, Ten gracz nie jest zalogowany., 1)
				return 1
			)
			
			// upewnimy się, że nadal sa w pobliżu siebie, bo przecież nie musiał od razu klikać tego ID
			Float:PosX, Float:PosY, Float:PosZ
			GetPlayerPos(selected_id, PosX, PosY, PosZ)
			
			if(GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(selected_id) || !IsPlayerInRangeOfPoint(playerid, 5.0, PosX, PosY, PosZ))
			(
				GuiMsg(playerid, Ten gracz nie jest w Twoim pobliżu., 1)
				return 1
			)			
			
			Float:health GetPlayerHealth(selected_id, health)
			if(health ) 50.0)
				PlayerCache(selected_id)(pBleeding) = 0

			DeleteItem(ItemInfo(MainPlayerTable(playerid))(iUID))
			MainPlayerTable(playerid) = 0

			SendClientMessage(selected_id, COLOR_DO, ** Opatrzono Cię. **)
			
			string(256)
			format(string, sizeof(string), * %s sięga po bandaż i owija nim postrzelone miejsce na ciele %s., PlayerName(playerid), PlayerName(selected_id))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	
	if(dialogid == D_SELECT_RADIOSTATION)
	(
		if(response)
		(
			station = strval(inputtext)
			PlayerCache(playerid)(pStation) = station

			GuiMsg(playerid, Ustawiłeś nową stację radiową!, 0)
			
			TextDrawHideForPlayer(playerid, Text:TextDrawSanNews)
			TextDrawShowForPlayer(playerid, Text:TextDrawRadio(station))
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_CAPTCHA)
	(
		if(response)
		(
			admin_id = MainPlayerTable(playerid)
			MainPlayerTable(playerid) = 0
			
			if (!strcmp(inputtext,  ))
			(
				GuiMsg(playerid, Błędnie wprowadziłeś kod., 1)
				MainPlayerTable(playerid) = 0
				return 1
			)
			
			if(strlen(inputtext) != strlen(PlayerCache(playerid)(pCaptcha)))
			(
				GuiMsg(playerid, Błędnie wprowadziłeś kod., 1)
				MainPlayerTable(playerid) = 0
				return 1
			)
			
			if(!strcmp(inputtext, PlayerCache(playerid)(pCaptcha)))
			(
				PlayerCache(admin_id)(pLastW) = playerid
				PlayerCache(playerid)(pLastW) = admin_id
				PlayerCache(playerid)(pLastWTo) = admin_id
				
				sending(256), string(128)
				format(sending, sizeof(sending), %s, PlayerCache(playerid)(pSendingCaptcha))
				
				if(strlen(sending) ( 78)
				(
					format(string, sizeof(string), (( » %s (%d): %s )), PlayerGlobalName(admin_id, COLOR_SEND_PW), admin_id, sending)
					SendClientMessage(playerid, COLOR_SEND_PW, string)
					
					format(string, sizeof(string), (( %s (%d): %s )), PlayerGlobalName(playerid, COLOR_GOT_PW), playerid, sending)
					SendClientMessage(admin_id, COLOR_GOT_PW, string)
				)
				else
				(
					pos = strfind(sending,  , true, strlen(sending) / 2)
					if(pos != -1)
					(
						text2(64)

						strmid(text2, sending, pos, strlen(sending))
						strdel(sending, pos, strlen(sending))

						format(string, sizeof(string), (( » %s (%d): %s )), PlayerGlobalName(admin_id, COLOR_SEND_PW), admin_id, sending)
						SendClientMessage(playerid, COLOR_SEND_PW, string)
						
						format(string, sizeof(string), (( %s (%d): %s )), PlayerGlobalName(playerid, COLOR_GOT_PW), playerid, sending)
						SendClientMessage(admin_id, COLOR_GOT_PW, string)
						
						
						format(string, sizeof(string), (( » %s (%d): %s )), PlayerGlobalName(admin_id, COLOR_SEND_PW), admin_id, text2)
						SendClientMessage(playerid, COLOR_SEND_PW, string)
						
						format(string, sizeof(string), (( %s (%d): %s )), PlayerGlobalName(playerid, COLOR_GOT_PW), playerid, text2)
						SendClientMessage(admin_id, COLOR_GOT_PW, string)
					)
				)
			)
			else
			(
				GuiMsg(playerid, Błędnie wprowadziłeś kod., 1)
				MainPlayerTable(playerid) = 0
				return 1
			)
		)
		else
		(
			GuiMsg(playerid, Błędnie wprowadziłeś kod., 1)
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	
	if(dialogid == D_USED_LIST)
	(
		if(response)
		(
			selected_id = listitem
			MainPlayerTable(playerid) = selected_id
			
			info(512)
			format(info, sizeof(info), Czy na pewno chcesz kupić %s za $%d?, UsedCars(selected_id)(uName), UsedCars(selected_id)(uCost))
			
			ShowPlayerDialog(playerid, D_USED_CONFIRM, DIALOG_STYLE_MSGBOX, Komis aut » potwierdzenie, info, Zatwierdź, Anuluj)
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_USED_CONFIRM)
	(
		if(response)
		(
			selected_id = MainPlayerTable(playerid)
			MainPlayerTable(playerid) = 0
			if(PlayerCache(playerid)(pCash) ( UsedCars(selected_id)(uCost))
			(
				GuiMsg(playerid, W komisie można płacić wyłącznie gotówką, nie masz jej wystarczająco dużo przy sobie., 1)
				return 1
			)
			
			// tworzenie zniszczeń wizualnych
			isDoor, isBonnet, isBoot
			isDoor = random(2)
			if(isDoor != 1)
				isBonnet = random(2)
			
			if(isBonnet != 1)
				isBoot = random(2)
				
			if(isDoor == 1)
				isDoor = 2
			
			if(isBonnet == 1)
				isBonnet = 2
				
			if(isBoot == 1)
				isBoot = 2
				
			// HP
			Float:max_hp = 899.0
			max_hp = max_hp - random(200)
			
			car_id = CreateCar(UsedCars(selected_id)(uModel), 2119.6765,-1154.4231,24.0709, 0.0, random(100), random(100), 6000000)
			CarInfo(car_id)(cOwnerType) = OWNER_PLAYER
			CarInfo(car_id)(cOwner) = PlayerCache(playerid)(pUID)
			SaveVehicle(car_id, SAVE_VEH_THINGS)
			
			hrp_GivePlayerMoney(playerid, -UsedCars(selected_id)(uCost))
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			// Dodanie ograniczen
			mysql_query_format(INSERT INTO hrp_removes VALUES(NULL, %d, %d, %d, %d, %d, %f), CarInfo(car_id)(cUID), isBonnet, isBoot, isDoor, 0, max_hp)
			getVehicleRemoves(car_id)
			
			hrp_VehicleActionLog((komis) Pojazd (UID: %d) zostal kupiony przez %s (UID: %d) za cene $%d, CarInfo(car_id)(cUID), PlayerName(playerid), PlayerCache(playerid)(pUID), UsedCars(selected_id)(uCost))
			GuiMsg(playerid, Wybrany pojazd został kupiony, powinien pojawić się na placu., 0)
		)
		else
			return 1
	)
	
	if(dialogid == D_DRUG_DEALING_START)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:		// olej
				(
					stringg(256)
					format(stringg, sizeof(stringg), ** Klient odszedł od %s kiwając głową na boki., PlayerName(playerid))
					ProxDetector(10.0, playerid, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
					PlayerCache(playerid)(pSelling) = false
				)
				case 1:		// handel
				(
					drug_list(512)
					foreach(Items, i)
					(
						if(ItemInfo(i)(iUID))
						(
							if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID) && ItemInfo(i)(iType) == ITEM_DRUG)
							(
								if(ItemInfo(i)(iValue2) ) 1)
									continue
									
								format(drug_list, sizeof(drug_list), %s\n%d. %s, drug_list, ItemInfo(i)(iUID), ItemInfo(i)(iName))
							)
						)
					)
					
					if(!strlen(drug_list))
					(
						GuiMsg(playerid, Nie posiadasz żadnej samarki z jednym gramem narkotyku., 0)
						PlayerCache(playerid)(pSelling) = false
						return 1
					)
					
					ShowPlayerDialog(playerid, D_DRUG_DEALING_CONTINUE, DIALOG_STYLE_LIST, Co chcesz sprzedać?, drug_list, Wybierz, Anuluj)
				)
			)
		)
		else
		(
			stringg(256)
			format(stringg, sizeof(stringg), ** Klient odszedł od %s kiwając głową na boki., PlayerName(playerid))
			ProxDetector(10.0, playerid, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
			PlayerCache(playerid)(pSelling) = false
			return 1
		)
	)
	
	if(dialogid == D_DRUG_DEALING_CONTINUE)
	(
		if(response)
		(
			rand = random(2)
			if(rand == 1)
			(
				sold_uid = strval(inputtext)
				MainPlayerTable(playerid) = sold_uid
				
				ShowPlayerDialog(playerid, D_DRUG_SELL, DIALOG_STYLE_LIST, Handel » akcja, 1. Sprzedaj towar tanio\n2. Sprzedaj towar drogo, Wybierz, Anuluj)
			)
			else
			(
				stringg(256)
				format(stringg, sizeof(stringg), ** Człowiek rozmawiający z %s krzyknął coś do niego, po czym odwrócił się i odszedł., PlayerName(playerid))
				ProxDetector(10.0, playerid, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
				PlayerCache(playerid)(pSelling) = false
			)
		)
		else
		(
			stringg(256)
			format(stringg, sizeof(stringg), ** Klient odszedł od %s kiwając głową na boki., PlayerName(playerid))
			ProxDetector(10.0, playerid, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
			PlayerCache(playerid)(pSelling) = false
			return 1
		)
	)
	
	if(dialogid == D_DRUG_SELL)
	(
		if(response)
		(
			sold_uid = MainPlayerTable(playerid)
			MainPlayerTable(playerid) = 0
			
			switch(listitem)
			(
				case 0:	// tanio
				(
					item_id = GetItemID(sold_uid), item_v1 = ItemInfo(item_id)(iValue1), s_cost = DrugCost(item_v1)
					hrp_GivePlayerMoney(playerid, s_cost)
					
					stringg(256)
					format(stringg, sizeof(stringg), ** Człowiek stojący przy %s odebrał od niego jakiś przedmiot, zaraz podał mu do ręki kilka banknotów., PlayerName(playerid))
					ProxDetector(10.0, playerid, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
					PlayerCache(playerid)(pSelling) = false
					DeleteItem(sold_uid)
					
					format(stringg, sizeof(stringg), ) Sprzedałeś towar za $%d!, s_cost)
					SendClientMessage(playerid, COLOR_ADMIN, stringg)
					
					PlayerCache(playerid)(pDailyDrugs) += 1
					hrp_MoneyActionLog(%s (UID: %d) zarobil $%d sprzedajac towar na cornerze., PlayerRealName(playerid), PlayerCache(playerid)(pUID), s_cost)
				)
				case 1:		// drogo
				(
					chance = random(2)
					if(chance == 1)
					(
						item_id = GetItemID(sold_uid), item_v1 = ItemInfo(item_id)(iValue1), s_cost = DrugCost(item_v1)
						
						Float:money = s_cost + floatround(DrugCost(item_v1)/4)
						hrp_GivePlayerMoney(playerid, floatround(money))
						
						stringg(256)
						format(stringg, sizeof(stringg), ** Człowiek stojący przy %s odebrał od niego jakiś przedmiot, zaraz podał mu do ręki kilka banknotów., PlayerName(playerid))
						ProxDetector(10.0, playerid, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
						PlayerCache(playerid)(pSelling) = false
						DeleteItem(sold_uid)
						
						format(stringg, sizeof(stringg), ) Sprzedałeś towar za $%d!, floatround(money))
						SendClientMessage(playerid, COLOR_ADMIN, stringg)
						
						PlayerCache(playerid)(pDailyDrugs) += 1
						hrp_MoneyActionLog(%s (UID: %d) zarobil $%d sprzedajac towar na cornerze., PlayerRealName(playerid), PlayerCache(playerid)(pUID), s_cost)
					)
					else
					(
						stringg(256)
						format(stringg, sizeof(stringg), ** Gość odszedł od %s rzucając jakieś kąśliwe uwagi w jego stronę., PlayerName(playerid))
						ProxDetector(10.0, playerid, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
						PlayerCache(playerid)(pSelling) = false
					)
				)
			)
		)
		else
		(
			stringg(256)
			format(stringg, sizeof(stringg), ** Klient odszedł od %s kiwając głową na boki., PlayerName(playerid))
			ProxDetector(10.0, playerid, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
			PlayerCache(playerid)(pSelling) = false
			return 1
		)
	)
	
	if(dialogid == D_SPARING_INVITE)
	(
		inviter_id = MainPlayerTable(playerid)
		MainPlayerTable(playerid) = 0
		
		if(response)		// Akceptuj
		(
			PlayerCache(playerid)(pSparing) = inviter_id
			PlayerCache(inviter_id)(pSparing) = playerid
			
			msg(128)
			format(msg, sizeof(msg), Gracz %s akceptował zaproszenie do sparingu., PlayerName(playerid))
			SendClientMessage(inviter_id, COLOR_INFO, msg)
			
			format(msg, sizeof(msg), Akceptowałeś zaproszenie do sparingu od gracza %s., PlayerName(inviter_id))
			SendClientMessage(playerid, COLOR_INFO, msg)
		)
		else					// Odrzucił
		(
			SendClientMessage(inviter_id, COLOR_INFO, Gracz odrzucił zaproszenie do sparingu.)
			return 1
		)
	)
	
	if(dialogid == D_OBJECTS_DELETE)
	(
		if(response)
		(
			doorid = GetPlayerDoorID(playerid), bool:jp2gmd = false
			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) == PlayerCache(playerid)(pUID))
			(
				jp2gmd = true
			)
			
			if(!jp2gmd)
			(
				GuiMsg(playerid, Te drzwi nie należą do Ciebie., 1)
				return 1
			)
			
			if(strlen(inputtext) != strlen(PlayerCache(playerid)(pCaptcha)))
			(
				GuiMsg(playerid, Błędnie wprowadziłeś kod., 1)
				return 1
			)
			
			if(!strcmp(inputtext, PlayerCache(playerid)(pCaptcha)))
			(
				for(object_id = 0  object_id ( MAX_OBJECTS object_id++)
				(
					if(IsValidDynamicObject(object_id))
					(
						if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID, DoorData(doorid)(dUID)))
						(
							hrp_DeleteObject(object_id)
							DestroyDynamicObject(object_id)
					  	)
					)
				)
			)
			else
			(
				GuiMsg(playerid, Błędnie wprowadziłeś kod., 1)
				return 1
			)
			
			GuiMsg(playerid, Usunąłeś wszystkie obiekty w tych drzwiach., 1)
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_PHONE_PASS)
	(
		if(response)
		(
			// Dialog na hasło do telefonu
			password = strval(inputtext), buffer(256)
			format(buffer, sizeof(buffer), SELECT * FROM hrp_phoneset WHERE set_password = %d AND set_phone = %d, password, PlayerCache(playerid)(pPhoneNumber))
			mysql_query(buffer)
			mysql_store_result()
			if(mysql_num_rows() ) 0)
			(
				mysql_free_result()
				phone_showTexts(playerid)
			)
			else
			(
				mysql_free_result()
				GuiMsg(playerid, Błędnie wprowadzony kod., 1)
				return 1
			)
			
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_PHONE_PASS_CHANGE)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
				(
					ShowPlayerDialog(playerid, D_PHONE_PASS_INPUT, DIALOG_STYLE_INPUT, Wprowadź hasło, Poniżej wpisz nowy kod, który chcesz mieć w telefonie - pamiętaj, że może mieć tylko 8 znaków.\n Przykład: 12345678, OK, Anuluj)
				)
				case 1:
				(
					mysql_query_format(UPDATE hrp_phoneset SET set_password = 0 WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
					GuiMsg(playerid, Hasło zostało usunięte! Od tej pory nie będzie potrzeby wpisywania go na nowo., 0)
				)
			)
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_PHONE_PASS_INPUT)
	(
		if(response)
		(
			password = strval(inputtext)
			if(password ( 0 || password ) 99999999)
			(
				GuiMsg(playerid, Zły format hasła., 1)
				return 1
			)
			
			mysql_query_format(UPDATE hrp_phoneset SET set_password = %d WHERE set_phone = %d, password, PlayerCache(playerid)(pPhoneNumber))
			GuiMsg(playerid, Hasło pomyślnie zmienione, od tej pory używaj go włączając telefon., 0)
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_PHONE_SELECT_WALLPAPER)
	(
		if(response)
		(
			switch(listitem)
			(
				case 0:
					mysql_query_format(UPDATE hrp_phoneset SET set_wallpaper = 0 WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
				case 1:
					mysql_query_format(UPDATE hrp_phoneset SET set_wallpaper = 1 WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
				case 2:
					mysql_query_format(UPDATE hrp_phoneset SET set_wallpaper = 2 WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
				case 3:
					mysql_query_format(UPDATE hrp_phoneset SET set_wallpaper = 3 WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
				case 4:
					mysql_query_format(UPDATE hrp_phoneset SET set_wallpaper = 4 WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
			)
			
			GuiMsg(playerid, Zmieniono tapetę w telefonie!, 0)
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_LAUNCH_SELECT_CHAR)
	(
		if(response)
		(
			SetPlayerName(playerid, inputtext)
			
			// Pobranie UID i GID
			data(256)
			mysql_query_format(SELECT char_uid, char_gid FROM hrp_characters WHERE BINARY char_name LIKE %s LIMIT 1, PlayerOriginalName(playerid))
			
			printf((mysql) Zaczynam sprawdzać gracza %s w bazie danych..., PlayerRealName(playerid))

			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)dd, PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))
				ClearChat(playerid)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystšpił błšd, Nie posiadasz u nas konta, załóż je na WEB_URL., OK, )

				printf((mysql) Gracz %s nie został odnaleziony w bazie danych - zostaje wyrzucony z serwera., PlayerRealName(playerid))
				Kick(playerid)
			)
			mysql_free_result()
			
			if(!IsGlobalLogged(PlayerCache(playerid)(pGID)))
			(	
				printf((mysql) Gracz %s (UID: %d, GID: %d) został odnaleziony w bazie danych - zalogowany launcherem., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))
				
				// Dodajemy pobranie adina, gsów itp.
				mysql_query_format(SELECT user_login, user_admin, user_premium, user_premium_time, user_gamepoints, user_color FROM live_users WHERE user_id = %d LIMIT 1, PlayerCache(playerid)(pGID))
				mysql_store_result()
				if(mysql_fetch_row(data, |))
				(
					printf((log) Logowanie gracza %s (UID: %d, GID: %d) przebiegło pomy?lnie., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))

					sscanf(data, p(|)s(64)ddddd, PlayerCache(playerid)(pGlobalName), PlayerCache(playerid)(pAdmin), PlayerCache(playerid)(pPremium), PlayerCache(playerid)(pPremiumTime), PlayerCache(playerid)(pGamePoints), PlayerCache(playerid)(pUserColor))
					AddPlayerLoginLog(playerid, true)
				)
				mysql_free_result()
				
				// Zalogowany
				Logged(playerid) = true
				OnPlayerLogin(playerid)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystšpił błšd, Obecnie na serwerze zalogowana jest już jaka? postać z tego konta globalnego., OK, )
				Kick(playerid)
			)
		)
		else
		(
			printf((launch)(kick) Wyrzucono gracza %s bo kliknal anuluj, PlayerOriginalName(playerid))
			Kick(playerid)
			return 1
		)
	)
	
	if(dialogid == D_BOX_SELECT_WEIGHT)
	(
		if( response )
		(
			switch(listitem)
			(
				case 0:
				(
					// 25KG
					PlayerCache(playerid)(pCarryBox) = BOX_LIGHT
				)
				case 1:
				(
					// 50 KG
					if(PlayerCache(playerid)(pStrength) ( 30.0)
					(
						GuiMsg(playerid, Nie masz wystarczająco siły!, 1)
						return 1
					)
					
					PlayerCache(playerid)(pCarryBox) = BOX_MEDIUM
				)
				case 2:
				(
					// 85 KG
					if(PlayerCache(playerid)(pStrength) ( 65.0)
					(
						GuiMsg(playerid, Nie masz wystarczająco siły!, 1)
						return 1
					)
					
					PlayerCache(playerid)(pCarryBox) = BOX_HUGE
				)
			)
			
			// Nosimy w tym momencie już.
			PlayerCache(playerid)(pCarryBoxPhase) = BOX_PHASE_CARRY
			SetPlayerPortAnimations(playerid)
			ShowPlayerTextDrawInfo(playerid, ~w~Uzyj klawisza ~r~~k~~CONVERSATION_NO~ ~w~by anulowac roznoszenie towarow w porcie. Aby odniesc paczke na miejsce udaj sie do markera i kliknij ~r~LPM)
			
			target = random(4)
			PlayerCache(playerid)(pCarryPoint) = target
			SetPlayerCheckpoint(playerid, BoxPositions(target)(bPosX), BoxPositions(target)(bPosY), BoxPositions(target)(bPosZ), 2.0)
			PlayerCache(playerid)(pCarryTries) += 1
		)
		else
		(
			return 1
		)
	)
	
	if(dialogid == D_VERIFICATE)
	(
		if(response)
		(
			// Sprawdź wpisany kod
			ga_code = strval(inputtext), get_string(256)
			
			format(get_string, sizeof(get_string), SELECT members.member_id FROM members INNER JOIN live_users ON live_users.user_id = members.member_gid WHERE live_users.user_id=%d LIMIT 1, PlayerCache(playerid)(pGID))
			mysql_query(get_string)
			mysql_store_result()
			member_id = mysql_fetch_int()
			mysql_free_result()

			ip(16)
			GetPlayerIp(playerid, ip, sizeof(ip))
			
			format(get_string, sizeof(get_string), ls-rp.ivam.pl/api/index.php?a=game&code=%d&userid=%d&usergid=%d&ip=%s, ga_code, member_id, PlayerCache(playerid)(pGID), ip)
			HTTP(playerid, HTTP_GET, get_string, , GoogleVerifyResponse)
		)
		else
		(
			ShowPlayerDialog(playerid, D_VERIFICATE, DIALOG_STYLE_INPUT, Weryfikacja dwuetapowa, Wypisz poniżej kod wygenerowany przez aplikację Google Authenticator., Gotowe, Anuluj)
			return 1
		)
	)
	
	if(dialogid == D_CORPO)
	(
		if(response)
		(
			PlayerCache(playerid)(pCarryTries) += 1
			if(PlayerCache(playerid)(pCarryTries) ) 9)
			(
				cmd_korporacja(playerid, )
				return 1
			)
			
			// Sprawdzanie wpisanego ciągu.
			switch(PlayerCache(playerid)(pCorpType))
			(
				case CORP_TYPE_TEXT:
				(
					/*
						Losowanie nowego pytania.
					*/
					originalstring(24)
					answer = random(20)
					switch(answer)
					(
						case 0:
							format(originalstring, sizeof(originalstring), kasa)
						case 1:
							format(originalstring, sizeof(originalstring), biuro)
						case 2:
							format(originalstring, sizeof(originalstring), wiezowiec)
						case 3:
							format(originalstring, sizeof(originalstring), biurko)
						case 4:
							format(originalstring, sizeof(originalstring), papiery)
						case 5:
							format(originalstring, sizeof(originalstring), okno)
						case 6:
							format(originalstring, sizeof(originalstring), auto)
						case 7:
							format(originalstring, sizeof(originalstring), inwestycja)
						case 8:
							format(originalstring, sizeof(originalstring), przyrost)
						case 9:
							format(originalstring, sizeof(originalstring), fortuna)
						case 10:
							format(originalstring, sizeof(originalstring), dokumenty)
						case 11:
							format(originalstring, sizeof(originalstring), komputer)
						case 12:
							format(originalstring, sizeof(originalstring), obroty)
						case 13:
							format(originalstring, sizeof(originalstring), strata)
						case 14:
							format(originalstring, sizeof(originalstring), dolary)
						case 15:
							format(originalstring, sizeof(originalstring), limuzyna)
						case 16:
							format(originalstring, sizeof(originalstring), podatki)
						case 17:
							format(originalstring, sizeof(originalstring), podatek)
						case 18:
							format(originalstring, sizeof(originalstring), stracic)
						case 19:
							format(originalstring, sizeof(originalstring), narzedzia)
						default:
							format(originalstring, sizeof(originalstring), korporacja)
					)
					
					scrambledstring(24) // this will contain the scrambled string
					rand
					for(i = 0, j = strlen(originalstring) i != j i++)
					(
					  do
					  (
						rand = random(j)
					  )
					  while(scrambledstring(rand) != 0)
					  scrambledstring(rand) = originalstring(i)
					)
					
					/*
						Koniec losowania następnego pytania.
					*/
					
					if(strcmp(inputtext, PlayerCache(playerid)(pCorpAnswer), true) == 0 && strlen(inputtext) ) 0)
					(
						// Correct
						hrp_GivePlayerMoney(playerid, 1)
						format(PlayerCache(playerid)(pCorpAnswer), 24, originalstring)
						
						message(256)
						format(message, sizeof(message), Odpowiedziałeś poprawnie, spróbuj jeszcze raz!\nUłóż słowo z podanych liter: %s, scrambledstring)
						ShowPlayerDialog(playerid, D_CORPO, DIALOG_STYLE_INPUT, Korporacja, message, Spróbuj, Anuluj)
					)
					else
					(
						// Uncorrect
						format(PlayerCache(playerid)(pCorpAnswer), 24, originalstring)
						message(256)
						format(message, sizeof(message), Odpowiedziałeś błędnie, spróbuj jeszcze raz!\nUłóż słowo z podanych liter: %s, scrambledstring)
						ShowPlayerDialog(playerid, D_CORPO, DIALOG_STYLE_INPUT, Korporacja, message, Spróbuj, Anuluj)
					)
				)
			)
		)
		else
		(
			// Przerwij robotę.
			cmd_korporacja(playerid, )
			return 1
		)
	)

	if(dialogid == D_JOIN_BOWLING)
	(
		// not used anymore
		return 1
	)

	if(dialogid == D_NEW_SAFE_PASSWORD)
	(
		if(response)
		(
			code = strval(inputtext)
			if(code != 0 && code )= 10000 && code (= 99999)
			(
				code = getSafeHash(code)
				if(code != 0)
				(
					itemid = MainPlayerTable(playerid)
					ItemInfo(itemid)(iValue1) = code
					mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Sejf, Kod zostal ustawiony., OK, )
				)
				else
				(
					ShowPlayerDialog(playerid, D_NEW_SAFE_PASSWORD, DIALOG_STYLE_INPUT, Sejf, Nie mozesz uzyc tego hasla.\nHaslo musi miec 5 cyfr!\nWpisz nowe haslo dla tego sejfu., OK, Anuluj)
				)
			)
			else
			(
				ShowPlayerDialog(playerid, D_NEW_SAFE_PASSWORD, DIALOG_STYLE_INPUT, Sejf, Nie mozesz uzyc tego hasla.\nHaslo musi miec 5 cyfr!\nWpisz nowe haslo dla tego sejfu., OK, Anuluj)
			)

			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)

	if(dialogid == D_SAFE_AUTH)
	(
		if(response)
		(
			code = strval(inputtext)
			if(code != 0 && code )= 10000 && code (= 99999)
			(
				hash = getSafeHash(code),
					itemid = MainPlayerTable(playerid)

				if(ItemInfo(itemid)(iValue1) == hash)
				(
					string(64)
					format(string, sizeof(string), Wyplac (max $%d)\nWplac (max $%d), ItemInfo(itemid)(iValue2), PlayerCache(playerid)(pCash))
					ShowPlayerDialog(playerid, D_SAFE_OP, DIALOG_STYLE_LIST, Sejf ) Wybierz operacje, string, OK, Anuluj)
					return 1
				)
				else
				(
					ShowPlayerDialog(playerid, D_SAFE_AUTH, DIALOG_STYLE_INPUT, Sejf, Nie poprawne haslo, wprowadz haslo, OK, Anuluj)
				)
			)
			else
			(
				ShowPlayerDialog(playerid, D_SAFE_AUTH, DIALOG_STYLE_INPUT, Sejf, Nie poprawne haslo, wprowadz haslo, OK, Anuluj)
			)

			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)

	if(dialogid == D_SAFE_OP)
	(
		if(response)
		(
			if(listitem == 0)
			(
				ShowPlayerDialog(playerid, D_SAFE_OUT_VALUE, DIALOG_STYLE_INPUT, Sejf ) Wyplac, Wpisz kwote ktora chcialbys wyplacic., OK, Anuluj)
				return 1
			)
			if(listitem == 1)
			(
				ShowPlayerDialog(playerid, D_SAFE_IN_VALUE, DIALOG_STYLE_INPUT, Sejf ) Wplac, Wpisz kwote ktora chcialbys wplacic., OK, Anuluj)
				return 1
			)
			
			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)

	if(dialogid == D_SAFE_IN_VALUE)
	(
		if(response)
		(
			cash = strval(inputtext)
			if(cash ) 0 && cash (= PlayerCache(playerid)(pCash))
			(
				itemid = MainPlayerTable(playerid)
				
				ItemInfo(itemid)(iValue2) += cash
				mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
				hrp_GivePlayerMoney(playerid, -cash)

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Gotowka zostala wrzucona do sejfu., OK, )
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie posiadasz tyle gotowki, OK, )
			)
			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)

	if(dialogid == D_SAFE_OUT_VALUE)
	(
		if(response)
		(
			cash = strval(inputtext),
				itemid = MainPlayerTable(playerid)

			if(cash ) 0 && cash (= ItemInfo(itemid)(iValue2))
			(
				ItemInfo(itemid)(iValue2) -= cash
				mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
				hrp_GivePlayerMoney(playerid, cash)

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Gotowka zostala wyciagnieta ze sejfu., OK, )
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, W sejfie nie ma tyle gotowki, OK, )
			)
			MainPlayerTable(playerid) = 0
			return 1
		)
		else
		(
			MainPlayerTable(playerid) = 0
			return 1
		)
	)
	
	// gotowanie narkotyków cooking.inc
	if(dialogid == D_COOK_SELECT)
	(
		cookid = PlayerCache(playerid)(pCookID)
		string(256)
		if(response)
		(
			CookData(cookid)(cDrug) = listitem
			format(string, sizeof(string), %s, RecipesData(listitem)(rName))
			
			hrp_TogglePlayerControllable(playerid, false)
			
			PlayerTextDrawSetString(playerid, CookThing(playerid), string)
			PlayerTextDrawShow(playerid, PlayerText:CookBG(playerid))
			SelectTextDraw(playerid, 0xFFFFFFFF)
			PlayerTextDrawShow(playerid, PlayerText:ActionCook(playerid))
			PlayerTextDrawShow(playerid, PlayerText:ActionAdd(playerid))
			PlayerTextDrawShow(playerid, PlayerText:ActionClose(playerid))
			PlayerTextDrawShow(playerid, PlayerText:CookInfo(playerid))
			PlayerTextDrawShow(playerid, PlayerText:CookThing(playerid))
			PlayerTextDrawShow(playerid, PlayerText:CookIngredients(playerid))
			
			return 1
		)		
		else
		(
			CookData(cookid)(cIsOccupied) = false
			PlayerCache(playerid)(pCookID) = -1
			return 1
		)
	)
	if(dialogid == D_COOK_ADD)
	(
		cookid = PlayerCache(playerid)(pCookID)
		if(response)
		(
			ingredient = CookData(cookid)(cIngredients), item_uid = strval(inputtext), item_id = GetItemID(item_uid), string(128)
			if(ingredient )= MAX_INGREDIENTS)
			(
				GuiMsg(playerid, Nie możesz dodać już więcej składników., 1)
				return 1
			)
			
			if(ItemInfo(item_id)(iType) == ITEM_DRUG && ItemInfo(item_id)(iValue1) == DRUG_COCAINE)
			(
				format(string, sizeof(string), proszek kokainowy)
				CookData(cookid)(cIngredient)(ingredient) = 24
			)
			else
			(
				format(string, sizeof(string), %s, IngredientsData(ItemInfo(item_id)(iValue1))(ingName))
				CookData(cookid)(cIngredient)(ingredient) = ItemInfo(item_id)(iValue1)
			)
			PlayerTextDrawSetString(playerid, CookIngredient(ingredient)(playerid), string)
			PlayerTextDrawShow(playerid, PlayerText:CookIngredient(ingredient)(playerid))
			CookData(cookid)(cIngredients)++
			
			DeleteItem(item_uid)

			format(string, sizeof(string), * %s dodaje %s do swojego wywaru., PlayerName(playerid), ItemInfo(item_id)(iName))
			FlashMe(playerid, string)
			ApplyAnimation(playerid,INT_HOUSE, wash_up, 4.1, 0, 0, 0, 0, 0, 1)
			return 1
		)
	)
	
	if(dialogid == D_DASHBOARD_ITEM)
	(
		if(response)
		(
			PlayerCache(playerid)(pManageItem) = strval(inputtext)
			ShowPlayerDialog(playerid, D_DASHBOARD_ITEM_PRICE, DIALOG_STYLE_INPUT, Sprzedaj przedmiot » Cena, Wprowadź poniżej cenę, jaką oczekujesz w zamian za przedmiot:, Oferuj, Anuluj)
		)
		else
		(
			PlayerCache(playerid)(pPlayerIDOffer) = INVALID_PLAYER_ID
		)
		return 1
	)
	if(dialogid == D_DASHBOARD_ITEM_PRICE)
	(
		if(response)
		(
			string(128), giveplayer_id = PlayerCache(playerid)(pPlayerIDOffer), item_uid = PlayerCache(playerid)(pManageItem)
			format(string, sizeof(string), przedmiot %d %d %d, giveplayer_id, item_uid, strval(inputtext))
			cmd_oferuj(playerid, string)
		)
		
		PlayerCache(playerid)(pManageItem) = 0
		PlayerCache(playerid)(pPlayerIDOffer) = INVALID_PLAYER_ID
		return 1
	)
	if(dialogid == D_DASHBOARD_PAY)
	(
		if(response)
		(
			string(128), giveplayer_id = PlayerCache(playerid)(pPlayerIDOffer)
			format(string, sizeof(string), %d %d, giveplayer_id, strval(inputtext))
			cmd_pay(playerid, string)
		)
		
		PlayerCache(playerid)(pPlayerIDOffer) = INVALID_PLAYER_ID
		return 1
	)
	if(dialogid == D_DASHBOARD_YO)
	(
		if(response)
		(
			string(128), giveplayer_id = PlayerCache(playerid)(pPlayerIDOffer)
			format(string, sizeof(string), %d %d, giveplayer_id, strval(inputtext))
			cmd_yo(playerid, string)
		)
		
		PlayerCache(playerid)(pPlayerIDOffer) = INVALID_PLAYER_ID
		return 1
	)
	if(dialogid == D_DASHBOARD_KISS)
	(
		if(response)
		(
			string(128), giveplayer_id = PlayerCache(playerid)(pPlayerIDOffer)
			format(string, sizeof(string), %d %d, giveplayer_id, strval(inputtext))
			cmd_kiss(playerid, string)
		)
		
		PlayerCache(playerid)(pPlayerIDOffer) = INVALID_PLAYER_ID
		return 1
	)
	if(dialogid == D_FCK_DECISION)
	(
		if(response)
		(
			killer_uid = PlayerCache(playerid)(pKiller),
				weapon_uid = PlayerCache(playerid)(pKillerWeapon)
				
			DropAllPlayerItems(playerid)
			item_uid = CreatePlayerCorpse(playerid, killer_uid, weapon_uid)
				
			SetItemDesc(item_uid, inputtext)
				
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postać została uśmiercona.\nOd tej pory postać, która została uśmiercona jest już nieaktywna.\n\nZostajesz wyrzucony z serwera., OK, )
			hrp_Block(playerid, -1, FCK, BLOCK_CHAR, 0, true)
			Kick(playerid)
			return 1
		)
		else
		(
			printf((FCK) Gracz %s powinien dostac FCK ale anulowal. Obczaj go., PlayerName(playerid))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Na skutek otrzymanych obrażeń, straciłeś przytomność.\nPoczekaj do czasu gdy się ockniesz, lub przyjedzie karetka., OK, )
			return 1
		)
	)
	
	return 1
)

stock GuiMsg(playerid, text(), isError)
(
	if(isError == 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystąpił błąd, text, OK, )
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, text, OK, )
	)
	
	return 1
)
















