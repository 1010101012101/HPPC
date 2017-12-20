vuser_init()
{
	

	web_set_sockets_option("SSL_VERSION", "TLS"); 
	lr_save_string("https://reststage.corp.cdw.com/external/v7.3/search", "INTERNAL_URL");
	
	//lr_save_string("https://webapistgvh1.corp.cdw.com/external/v7.0/search", "INTERNAL_URL");
	lr_save_string("Basic MkZEN0JBNkI0Mjk4NDExNThGMTVCRjYxODczMEFEQTU6MUY3MjVGQjRGOTQ2NDc0OUE1NUFCNkMxN0RCNTZFNDg=","BASIC");
	lr_save_string(lr_get_attrib_string("Site"), "Site_Name");

	Authorization();
	
	return 0;
}


void Authorization() 
{
	web_reg_save_param("TOKEN","LB=\"access_token\":\"","RB=\"","Notfound=warning", "Ordinal=All", LAST);
	web_add_header("Authorization",lr_eval_string("{BASIC}"));
   	web_submit_data("GetToken",
      "Action={INTERNAL_URL}/token",  
           "Method=POST",  
           "RecContentType=text/html",  
           "Snapshot=t001.inf",  
           "Mode=HTML",  
           ITEMDATA,  
           "Name=grant_type", "Value=client_credentials", ENDITEM,  
           LAST); 
      if (!atoi(lr_eval_string("{TOKEN_count}"))) 
           { 
                lr_output_message("Failed to get token"); 
                lr_abort(); 
           } 
      lr_save_string(lr_eval_string("{TOKEN_1}"),"APITOKEN"); 
     } 
      

