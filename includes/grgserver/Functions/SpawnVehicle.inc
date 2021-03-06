SpawnVehicle(playerID, modelID, color1, color2, showMessage)
{
	if (!modelID)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:64("The vehicle was not found!"));
		}
		return false;
	}
	if (modelID < 400 || modelID > 611)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:65("The model ID must be between 400 and 611!"));
		}
		return false;
	}
	if (color1 < -1 || color1 > 127 || color2 < -1 || color2 > 127)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:63("The color must be between 0 and 127!"));
		}
		return false;
	}
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:angle;
	GetPlayerPos(playerID, posX, posY, posZ);
	GetPlayerFacingAngle(playerID, angle);
	new vehicleID = CreateVehicleEx(modelID, posX, posY, posZ, angle, color1, color2, false);
	if (!vehicleID)
	{
		if (showMessage)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:461("The vehicle could not be spawned!"));
		}
		return false;
	}
	VehicleProperty:vehicleID[HASNAVI] = true;
	LinkVehicleToInterior(vehicleID, GetPlayerInterior(playerID));
	SetVehicleVirtualWorld(vehicleID, GetPlayerVirtualWorld(playerID));
	PutPlayerInVehicle(playerID, vehicleID, 0);
	if (showMessage)
	{
		SendClientMessageEx(playerID, COLOR_INFO, StringID:62("The vehicle has been spawned"));
	}
	return true;
}