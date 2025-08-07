stock SetPlayerLaundryAnimations(playerid)
(
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY)
	SetPlayerAttachedObject(playerid, SLOT_TRYING, 1576, 6, 0.10, -0.030999, -0.155, -112.5, -5.89993, 88.1001, 1.0, 1.0, 1.0, 0xFFFF8C2C)
	return 1
)

stock SetPlayerWorkshopAnimations(playerid)
(
	hrp_TogglePlayerControllable(playerid, false)
	ApplyAnimation(playerid, SWORD, sword_IDLE, 4.1, 0, 0, 0, 1, 0, 1)
	return 1
)

stock StopPlayerAnimations(playerid)
(
	hrp_TogglePlayerControllable(playerid, true)
	ClearAnimations(playerid)
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE)
	RemovePlayerAttachedObject(playerid, SLOT_TRYING)
	return 1
)

stock StopPlayerPrisonWork(playerid)
(
	StopPlayerAnimations(playerid)
	
	PlayerCache(playerid)(pWorkingNow) = 0
	PlayerCache(playerid)(pWorkingPhase) = 0
)

CMD:praca(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		GuiMsg(playerid, Nie możesz tego zrobić będąc nieprzytomnym., 1)
		return 1
	)
	if(!PlayerCache(playerid)(pArrest))
	(
		GuiMsg(playerid, Tej komendy możesz użyć do pracy tylko będąc w areszcie., 1)
		return 1
	)
	
	if(PlayerCache(playerid)(pWorkingNow))
	(
		GuiMsg(playerid, Pracowałeś, obecnie przerwałeś pracę w więzieniu., 0)
		StopPlayerPrisonWork(playerid)
		return 1
	)
	
	if(PlayerCache(playerid)(pWorkRepeat) )= 10)
	(
		GuiMsg(playerid, Wyczerpałeś dzienny limit pracy, odpocznij., 0)
		return 1
	)
	
	type(32)
	if(sscanf(params, s(32), type))
	(
		hrp_Tip(playerid, /praca (pralnia | warsztat))
		return 1
	)
	
	// sprawdzanie limitu prac dziennych
	
	if(!strcmp(type, pralnia, true))
	(
		if(PlayerCache(playerid)(pWorkingNow))
		(
			GuiMsg(playerid, Obecnie pracujesz.\nAby przerwać pracę użyj komendy /praca., 1)
			return 1
		)
		if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1782.0901, -1548.1317, 40.8159))
		(
			GuiMsg(playerid, Aby rozpocząć pracę w pralni musisz się tam znajdować., 1)
			return 1
		)
		PlayerCache(playerid)(pWorkingNow) = WORK_LAUNDRY
		PlayerCache(playerid)(pWorkingPhase) = LAUNDRY_UNLOADED
		GuiMsg(playerid, Rozpocząłeś pracę jako pomocnik w pralni!\nTeraz musisz udać się do poszczególnych cel aby zebrać brudną odzież więźniów oraz prześcieradła z powrotem do pralni.\nBędąc w celi aby podnieść rzeczy użyj klawisza H (klakson)., 0)
	)
	else if(!strcmp(type, warsztat, true))
	(
		if(PlayerCache(playerid)(pWorkingNow))
		(
			GuiMsg(playerid, Obecnie pracujesz.\nAby przerwać pracę użyj komendy /praca., 1)
			return 1
		)
		if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1764.4370, -1534.9044, 39.9441))
		(
			GuiMsg(playerid, Aby rozpocząć pracę w warsztacie musisz znajdować się przy stanowisku., 1)
			return 1
		)
		PlayerCache(playerid)(pWorkingNow) = WORK_WORKSHOP
		PlayerCache(playerid)(pWorkingPhase) = WORKSHOP_WAITING
		PlayerCache(playerid)(pWorkingRepeat) = 0
		GuiMsg(playerid, Rozpocząłeś pracę jako cieśla w warsztacie!\nAby rozpocząć pracę użyj klawisza H (klakson). Jeżeli chcesz przerwać pracę ponownie użyj klawisza H.\nPo rozpoczęciu pracy musisz w określonym czasie wcisnąć wystarczającą dużą ilość LPM (lewy przycisk myszki), strażnikowi zależy na czasie., 0)
	)
	else
	(
		hrp_Tip(playerid, /praca (pralnia | warsztat))
	)
	
	return 1
)