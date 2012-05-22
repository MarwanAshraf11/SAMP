PCMD:spawnvehicle[MAPPER](playerID, params[], 122)
{
	new vehicleName[20];
	new modelID;
	new color1;
	new color2;
	if (sscanf(params, "ddd", modelID, color1, color2))
	{
		if (!sscanf(params, "d", modelID))
		{
			color1 = random(127);
			color2 = random(127);
		}
		else
		{
			if (sscanf(params, "sdd", vehicleName, color1, color2))
			{
				if (!sscanf(params, "s", vehicleName))
				{
					color1 = random(127);
					color2 = random(127);
				}
				else
				{
					CmdUsageMsg(playerID, "spawnvehicle", "ModelID/Name/t:Type", "[Color1]", "[Color2]");
					return COMMAND_USAGE;
				}
			}
			new type;
			new parameter[16];
			if (sscanf(vehicleName, "p:cs", type, parameter))
			{
				MySQLQuery("SELECT * FROM `vehiclemodels` WHERE `Name` LIKE '%s' LIMIT 100", str_replace("*", "%%", MySQLEscapeString(vehicleName)));
				mysql_store_result();
				if (!mysql_num_rows() && strfind(vehicleName, "*") == -1)
				{
					mysql_free_result();
					MySQLQuery("SELECT * FROM `vehiclemodels` WHERE `Name` LIKE '%%%s%%' LIMIT 100", MySQLEscapeString(vehicleName));
					mysql_store_result();
				}
			}
			else
			{
				switch (type)
				{
					case 't':
					{
						MySQLQuery("SELECT * FROM `vehiclemodels` WHERE `Type` LIKE '%s' LIMIT 100", str_replace("*", "%%", MySQLEscapeString(parameter)));
						mysql_store_result();
						if (!mysql_num_rows() && strfind(parameter, "*") == -1)
						{
							mysql_free_result();
							MySQLQuery("SELECT * FROM `vehiclemodels` WHERE `Type` LIKE '%%%s%%' LIMIT 100", MySQLEscapeString(parameter));
							mysql_store_result();
						}
					}
					default:
					{
						SendClientMessageEx(playerID, COLOR_ERROR, 58);
						return COMMAND_ERROR;
					}
				}
			}
			if (mysql_num_rows() > 1)
			{
				new vehicleList[2048];
				while (FetchMySQLRow())
				{
					if (strlen(vehicleList))
					{
						strcat(vehicleList, "\n");
					}
					Format:vehicleList("%s%s:%s", vehicleList, GetMySQLField("ID"), GetMySQLField("Name"));
				}
				PVar:playerID[SPAWNVEHICLE_COLOR1] = color1;
				PVar:playerID[SPAWNVEHICLE_COLOR2] = color2;
				FormatNew:title[64](LanguageString(playerID, 122), vehicleName);
				CreateDialog(playerID, "SpawnVehicle", DIALOG_STYLE_LIST, title, vehicleList, LanguageString(playerID, 205), LanguageString(playerID, 165));
				modelID = -1;
			}
			else
			{
				modelID = strval(GetMySQLField("ID"));
			}
			mysql_free_result();
		}
	}
	if (modelID == -1)
	{
		return COMMAND_OK;
	}
	if (SpawnVehicle(playerID, modelID, color1, color2, true))
	{
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}