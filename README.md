# therealshop-authenticator-logger
Grab the account information including 2 step from the trash authenticator

https://therealshop.exaccess.com/ is an account selling website (resell on plati.ru) that has their custom authenticator which pastes the login info directly inside ubisoft/steam/epic games to avoid giving the login information to the user (really dumb idea).
this program has 40 detections on [virustotal](https://www.virustotal.com/gui/file/9a5ba2c3edadd81ed23f5e7c218320df367a4c86c2deff75742941ce652c612d) and is extremely suspicious (recommend to run in vm to get the account information)

The logger waits for the login information to be set to the clipboard and dumps it,
once the email and password is dumped it waits for the 2fa code and before their authenticator has a chance to use it, it closes the authenticator and logs the 2fa
