function validate_signup()
{
	var counter = 0;
	if (document.getElementById("pas").value == "")
	{
		counter++;
		//document.getElementById("passErrSign").css('display', 'block');
	}
	if (document.getElementById("pas2").value == "" || document.getElementById("pas2").value !== document.getElementById("pas").value)
	{
		counter++;
		//document.getElementById("rPassErrSign").css('display', 'block');
		document.getElementById("pas2").value = '';
	}
	return counter ? false : true;
}


