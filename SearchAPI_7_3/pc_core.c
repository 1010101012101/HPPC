
void pc_IterationInit()
{
	pc_browserCleanup();
	pc_parseGroupName();
	get_siteURL_bySiteKey();

}


void pc_parseGroupName()
{
	char *pStart = (char *)malloc(128);
	char *pEnd = (char *)malloc(128);

	char *pStartToDel;
	char *pEndToDel;

	   pStartToDel = pStart;
	   pEndToDel = pEnd;

	if(!(strcmp("None", lr_eval_string ("{PC_groupName}")))) 	
		lr_save_string ("corp_logged", "PC_groupName");
	
	strcpy(pStart,lr_eval_string ("{PC_groupName}"));

	pEnd=(char*) strstr(pStart,"_");	*pEnd = '\0';
	lr_save_string(pStart,"SITE_KEY");	pStart = pEnd+1;

	lr_save_string(pStart,"LOGGED_KEY");
	
	free(pStartToDel);
	free(pEndToDel);
	
}

void save_param_by_site(char *basicParamName)
{
	char paramName[256];
	sprintf(paramName, "{%s_%s}", basicParamName, lr_eval_string("{SITE_KEY}"));
	lr_save_string(lr_eval_string(paramName),basicParamName);
}

void get_siteURL_bySiteKey()
{
	if (!strcmp("corp",lr_eval_string("{SITE_KEY}"))) lr_save_string("webstage2vh.corp.cdw.com","SITE_URL");
	else if (!strcmp("gov",lr_eval_string("{SITE_KEY}"))) lr_save_string("webstage7.corp.cdwg.com","SITE_URL");
	else if (!strcmp("ca",lr_eval_string("{SITE_KEY}"))) lr_save_string("webstage7.corp.cdw.ca","SITE_URL");
}

void pc_browserCleanup()
{
web_cleanup_cookies();
web_cache_cleanup();
}



