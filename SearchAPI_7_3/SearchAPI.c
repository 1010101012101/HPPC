SearchAPI()
{
	int HttpRetCode;
	char *tr_prefix  = (char *)malloc(128);
	
	web_cache_cleanup();
	web_add_header("Authorization",lr_eval_string("bearer {APITOKEN}"));
    web_add_header("Accept","application/json"); 
    
    web_reg_save_param("JsonData","LB=","RB=","Search=Body",LAST);

   if (!strcmp("cdwc",lr_eval_string("{Site_Name}")))
	{
   	sprintf(tr_prefix, lr_eval_string("Corp_{TrName_Corp}"));	
   	lr_save_string(tr_prefix,"TR_NAME_PARAM");
	lr_save_string(lr_eval_string("{SearchURL_Corp}"),"SURL_PARAM");
	//lr_save_string(lr_eval_string(""),"APIstr_PARAM");
    //lr_output_message("%s,%s",lr_eval_string("{SURL_PARAM}"),lr_eval_string("{APIstr_PARAM}"));
	}
	else if (!strcmp("cdwca",lr_eval_string("{Site_Name}")))
	{
	sprintf(tr_prefix, lr_eval_string("CA_{TrName_CA}"));	
   	lr_save_string(tr_prefix,"TR_NAME_PARAM");
	lr_save_string(lr_eval_string("{SearchURL_CA}"),"SURL_PARAM");
	//lr_save_string(lr_eval_string(""),"APIstr_PARAM");
	}
	else 
	{
	sprintf(tr_prefix, lr_eval_string("GOV_{TrName_Gov}"));	
   	lr_save_string(tr_prefix,"TR_NAME_PARAM");
	lr_save_string(lr_eval_string("{SearchURL_Gov}"),"SURL_PARAM");
	//lr_save_string(lr_eval_string(""),"APIstr_PARAM");
	
	}
   
    addDynaTraceHeader("NA={TR_NAME_PARAM};PC={SURL_PARAM}");
    sprintf(tr_prefix, lr_eval_string("SearchAPI_{TR_NAME_PARAM}"));
    lr_save_string(tr_prefix, "TR_NAME");
    
    lr_start_transaction("SearchAPI_Search");
    lr_start_transaction(lr_eval_string("{TR_NAME}"));
    
    
    web_url("SearchProducts",
    	"URL={INTERNAL_URL}/products/{Site_Name}/async{SURL_PARAM}",  
        "TargetFrame=",  
        "Resource=0",  
        "RecContentType=text/html",  
        "Referer=",  
        "Snapshot=t002.inf",  
        "Mode=HTML",  
        LAST); 


   HttpRetCode = web_get_int_property(HTTP_INFO_RETURN_CODE);
   if (HttpRetCode == 200)
   {
     lr_end_transaction(lr_eval_string("{TR_NAME}"),LR_AUTO);
     lr_end_transaction("SearchAPI_Search",LR_AUTO);
   }
     else
     {
     	lr_end_transaction(lr_eval_string("{TR_NAME}"),LR_FAIL);
      lr_end_transaction("SearchAPI_Search",LR_FAIL);
     }
    
//   web_js_run("Code=APItimeout(LR.getParam('JsonData'));", "ResultParam=APItimeout", SOURCES, "File=GetdatafromJSONresponse.js", ENDITEM, LAST); 
//   web_js_run("Code=getNoofProducts(LR.getParam('JsonData'));", "ResultParam=NoofProducts", SOURCES, "File=GetdatafromJSONresponse.js", ENDITEM, LAST); 
//    lr_output_message("%s,%s",lr_eval_string("{NoofProducts}"),lr_eval_string("{APItimeout}"));
//      	
//    if(!strcmp("1",lr_eval_string("{APItimeout}")))	
//    {
//    web_js_run("Code=APItimeoutcode(LR.getParam('JsonData'));", "ResultParam=APItimeoutcode", SOURCES, "File=GetdatafromJSONresponse.js", ENDITEM, LAST); 
//    web_js_run("Code=APItimeoutmessage(LR.getParam('JsonData'));", "ResultParam=APItimeoutmessage", SOURCES, "File=GetdatafromJSONresponse.js", ENDITEM, LAST);
//     lr_output_message("%s,%s",lr_eval_string("{APItimeoutcode}"),lr_eval_string("{APItimeoutmessage}"));
//     lr_end_transaction(lr_eval_string("{TR_NAME}"),LR_FAIL);
//    }
//   else
//   	lr_end_transaction(lr_eval_string("{TR_NAME}"),LR_AUTO);
   
   
	free(tr_prefix);
     
	return 0;
}
