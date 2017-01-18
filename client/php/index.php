<?php
class Ip2C {
	private $server_ip;
	private $server_port;
	private $sock;
	private $connection;
	private $buffersize = 32;
	function __construct($server_ip = "127.0.0.1", $server_port = 8033) {
		$this->server_ip = $server_ip;
		$this->server_port = $server_port;
		$this->sock = socket_create ( AF_INET, SOCK_STREAM, SOL_TCP ) or die ( "cannot create socket\n" );
		$this->connection = socket_connect ( $this->sock, $this->server_ip, $this->server_port ) or die ( "cannot connect to server:'$this->server_ip' at port:'$this->server_port'\n" );
	}
	function getCountry($ip) {
		if (! @socket_write ( $this->sock, $ip, strlen ( $ip ) )) {
			echo "send error\n";
			socket_close ( $this->sock );
			exit ();
		}
		$ret = "";
		$ret = socket_read ( $this->sock, $this->buffersize, PHP_BINARY_READ);
		return $ret;
	}
	function close() {
		socket_close ( $this->sock );
	}

public static function GetIp() {
        $realip = '';
        $unknown = 'unknown';
        if (isset($_SERVER)) {
            if (isset($_SERVER['HTTP_X_FORWARDED_FOR']) && !empty($_SERVER['HTTP_X_FORWARDED_FOR']) && strcasecmp($_SERVER['HTTP_X_FORWARDED_FOR'], $unknown)) {
                $arr = explode(',', $_SERVER['HTTP_X_FORWARDED_FOR']);
                foreach ($arr as $ip) {
                    $ip = trim($ip);
                    if ($ip != 'unknown') {
                        $realip = $ip;
                        break;
                    }
                }
            } else if (isset($_SERVER['HTTP_CLIENT_IP']) && !empty($_SERVER['HTTP_CLIENT_IP']) && strcasecmp($_SERVER['HTTP_CLIENT_IP'], $unknown)) {
                $realip = $_SERVER['HTTP_CLIENT_IP'];
            } else if (isset($_SERVER['REMOTE_ADDR']) && !empty($_SERVER['REMOTE_ADDR']) && strcasecmp($_SERVER['REMOTE_ADDR'], $unknown)) {
                $realip = $_SERVER['REMOTE_ADDR'];
            } else {
                $realip = $unknown;
            }
        } else {
            if (getenv('HTTP_X_FORWARDED_FOR') && strcasecmp(getenv('HTTP_X_FORWARDED_FOR'), $unknown)) {
                $realip = getenv("HTTP_X_FORWARDED_FOR");
            } else if (getenv('HTTP_CLIENT_IP') && strcasecmp(getenv('HTTP_CLIENT_IP'), $unknown)) {
                $realip = getenv("HTTP_CLIENT_IP");
            } else if (getenv('REMOTE_ADDR') && strcasecmp(getenv('REMOTE_ADDR'), $unknown)) {
                $realip = getenv("REMOTE_ADDR");
            } else {
                $realip = $unknown;
            }
        }
        $realip = preg_match("/[\d\.]{7,15}/", $realip, $matches) ? $matches[0] : $unknown;
        return $realip;
    }

    public static function GetIpLookupEx($ip = '') {
    	if (empty($ip)) {
    		$ip = self::GetIp();
    	}
    	$ip2c = new Ip2C();
        $reValue = $ip2c->getCountry($ip);

        if(!strncasecmp($reValue, "NOTFOUND",8))
                $reValue = false;
        else
                $reValue = substr($reValue,0,2);
        $ip2c->close();
        return $reValue;
    }

	public static function clear_urlcan($url){

		$rstr='';
		$tmparr=parse_url($url);

		$rstr=empty($tmparr['scheme'])?'':$tmparr['scheme'].'';
		$rstr.=$tmparr['host'].$tmparr['path'];

		return $rstr;
	}


    	public static function checkLocation() {
		$request = $_SERVER['REQUEST_URI'];
		if ( !isset($request) )
			$request = '/';

		if ( isset ( $_GET['la'] ) && $_GET['la'] === 'e' ){
			setcookie ( 'cid', 'US', time () + 3600 * 24 * 3);
			header('HTTP/1.1 301 Moved Permanently');
			$newurl=self::clear_urlcan($request);
			header('Location:'.$newurl);
		}elseif ( isset ( $_GET['la'] ) && $_GET['la'] === 'c' ){
                        setcookie ( 'cid', 'CN', time () + 3600 * 24 * 3);
			$newurl=self::clear_urlcan($request);
                        header('HTTP/1.1 301 Moved Permanently');
                        header('Location:'.$newurl);
                }else{
			if (!isset ( $_COOKIE["cid"] )){
				$c = self::GetIpLookupEx();
				if ($c){
					setcookie ( 'cid', $c, time () + 3600 * 24 * 3);
				}
			}else{
				$c = $_COOKIE["cid"];
			}
			if ($c){
                        	if(! strcasecmp ( $c, 'cn' ) && (!strpos($_SERVER['REQUEST_URI'],'zh-hans'))) {
					header('HTTP/1.1 301 Moved Permanently');
	                                header('Location:/zh-hans'.$request);
                        	}
			}
                }	
	}
}
Ip2C::checkLocation();
?>
