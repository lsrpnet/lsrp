/*
	Porty
*/

stock SetPlayerPortAnimations(playerid)
(
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY)
	SetPlayerAttachedObject(playerid, SLOT_TRYING, 2968, 6, 0.11, 0.295999, -0.247, -112.5, 2.89993, 78.1001, 1.0, 1.0, 1.0)
	return 1
)

stock StopPlayerPortAnimations(playerid)
(
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE)
	RemovePlayerAttachedObject(playerid, SLOT_TRYING)
	return 1
)

stock StopPlayerCarryPort(playerid)
(
	// Wyłączenie noszenia etc.
	StopPlayerPortAnimations(playerid)
	PlayerCache(playerid)(pCarryBox) = BOX_NONE
	PlayerCache(playerid)(pCarryBoxPhase) = BOX_PHASE_NONE
	PlayerCache(playerid)(pCarryPoint) = 0
	DisablePlayerCheckpoint(playerid)
	HidePlayerTextDrawInfo(playerid)
	return 1
)

CMD:port(playerid, params())
(
	if(PlayerCache(playerid)(pCarryTries) ) 2)
	(
		GuiMsg(playerid, Nie ma teraz żadnego ładunku do wzięcia, poczekaj chwilę., 1)
		return 1
	)
	
	if(PlayerCache(playerid)(pCarryBoxPhase) == BOX_PHASE_CARRY)
	(
		target_id = PlayerCache(playerid)(pCarryPoint)
		if( IsPlayerInRangeOfPoint(playerid, 5.0, BoxPositions(target_id)(bPosX), BoxPositions(target_id)(bPosY), BoxPositions(target_id)(bPosZ)) )
		(
			// zakończ noszenie
			box_id = PlayerCache(playerid)(pCarryBox)
			if(box_id == BOX_LIGHT)
			(
				GuiMsg(playerid, Odłożyłeś ładunek na miejsce.\nOtrzymałeś: $2!, 0)
				hrp_GivePlayerMoney(playerid, 2)
			)
			else if(box_id == BOX_MEDIUM)
			(
				GuiMsg(playerid, Odłożyłeś ładunek na miejsce.\nOtrzymałeś: $4!, 0)
				hrp_GivePlayerMoney(playerid, 4)
			)
			else if(box_id == BOX_HUGE)
			(
				GuiMsg(playerid, Odłożyłeś ładunek na miejsce.\nOtrzymałeś: $6!, 0)
				hrp_GivePlayerMoney(playerid, 6)
			)
			
			StopPlayerCarryPort(playerid)
			HidePlayerTextDrawInfo(playerid)
			
			ApplyAnimation(playerid, ROB_BANK, CAT_Safe_Rob, 4.0, 0, 0, 0, 0, 0, 1)
		)
		else
		(
			GuiMsg(playerid, Nie jesteś w miejscu rozładunku.\nUdaj się do markera i wpisz komendę raz jeszcze., 1)
		)
		
		return 1
	)
	
	if(PlayerCache(playerid)(pCarryBox) == BOX_NONE)
	(
		if(IsPlayerInRangeOfPoint(playerid, 5.0, 2824.2646,-2435.8899,12.0889))
		(
			// Zacznij paczki
			DisablePlayerCheckpoint(playerid)
			ShowPlayerDialog(playerid, D_BOX_SELECT_WEIGHT, DIALOG_STYLE_LIST, Wybierz wagę, 1. 25KG\n2. 50KG\n3. 85KG, Wybierz, Anuluj)
		)
		else
		(
			// Postaw checkpoint, daj info, że nie jest w pobliżu
			SetPlayerCheckpoint(playerid, 2824.2646,-2435.8899,12.0889, 2.0)
			GuiMsg(playerid, Udaj się do wskazanego punktu by zacząć roznosić ładunki w porcie., 0)
		)
	)
	
	return 1
)