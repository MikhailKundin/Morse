function validate_signup()
{
	var counter = 0;
	if (document.getElementById("pas").value == "" || document.getElementById("pas2").value == "")
	{
		counter++;
		document.getElementById("err").innerHTML = 'Пароль необходимо ввести дважды';
	}
	if (document.getElementById("pas2").value == "" || document.getElementById("pas2").value !== document.getElementById("pas").value)
	{
		counter++;
		document.getElementById("err").innerHTML = 'Пароли должны совпадать';
	}
	if (document.getElementById("log").value == "")
	{
		counter++;
		document.getElementById("err").innerHTML = 'Необходимо ввести логин';
	}
	return counter ? false : true;
}
function validate_signin()
{
	var counter = 0;
	if (document.getElementById("log").value == "" )
	{
		counter++;
		document.getElementById("err").innerHTML = 'Необходимо ввести логин';
	}
	if (document.getElementById("pas").value == "")
	{
		counter++;
		document.getElementById("err").innerHTML = 'Необходимо ввести пароль';
	}
	return counter ? false : true;
}
function validate_word()
{
	var counter = 0;
	if (document.getElementById("code").value == "" )
	{
		counter++;
		document.getElementById("err").innerHTML = 'Необходимо ввести ответ';
	}
	
	return counter ? false : true;
}