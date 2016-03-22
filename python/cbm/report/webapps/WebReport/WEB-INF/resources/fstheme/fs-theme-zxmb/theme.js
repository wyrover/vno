(function ($) {    
	FS.THEME = $.extend(true, FS.THEME, {   
		config4MenuTree: {                      
		    onAfterInit: function (element) {
		        Menu.Size();
		        $(".fs-menutree ul > li").each(function (idx) {
		            $(this).find(".fs-menu-icon").html('<img class="limg" src="${servletURL}?op=resource&resource=/fstheme/fs-theme-zxmb/xt' + idx + '.png\"/>');
		        });
		        Menu.Sec = setInterval(Menu.SecFun, 200);
		    }
		},
		config4frame: {
		    resizable: false
		},
		config4navigation: {
		    onBeforeInit: function () {
            },  //初始化前事件
		    onAfterInit: function () {
				$.ajax({
                    url: FR.servletURL + "?op=fs_main&cmd=module_getrootreports",
                    type: 'POST',
                    data: {id: -1},
                    success: function (res, status) {
                        var nodes = $.parseJSON(res);
                        $.ajax({
                            url: FR.servletURL + "?op=fs_main&cmd=getmoduleitems",
                            type: 'POST',
                            async: false,
                            data: {id: 1},
                            success: function (res) {
                                nodes.push($.parseJSON(res));
                                if (nodes.length == 0) {
                                    return;
                                }
                                Menu.Nodes = nodes;
                                var $ul = $('<ul class="node-navi"/>').appendTo($('#fs-frame-header'));
                                Menu.Init();
                                var htmls = "",xname="";
                                for (var i = 0; i < nodes.length; i++) {
                                    xname = nodes[i].text;
                                    xname = xname == "平台管理" ? "管理系统" : xname;
                                    htmls += '<li class="lius" xt="' + i + '"><div class="tb"></div><div class="nr">' + xname + '</div></li>';
                                }
                                $ul.html(htmls);
                                Menu.Btn();
                                Menu.SecFlag = true;
                            }
                        });
					}
				});
            }//初始化后事件
        }, 
		config4tabPane: {
            style: 'alpha',            
			isCollapsible: false,           
			hasHomepageBtn: true
        }
    });
})(jQuery);

var Menu = {
    SecFlag: false,
    Sec: null,
    Nodes: null,
    Flag: true,
    SecFun: function () {
        if (Menu.SecFlag) {
            $(".node-navi li").eq(0).click();
            Menu.Size();
            clearInterval(Menu.Sec);
        }
    },
    Init: function () {
        $(window).resize(function () {
            Menu.SetFlag();
            (function () {
                setTimeout(function () {
                    $("#fs-frame-body").css("top", "80px").height(document.documentElement.clientHeight - 80);
                    $("#fs-frame-header").css("height", "80px");
                }, 500)
            })();
        });
        this.Btn();
    },
    SetFlag:function(){
        var pw = document.documentElement.clientWidth - 570;
        var ph = document.documentElement.clientHeight;
        if ($(".fs-menutree ul > li").length * 88 - pw > 0) {
            Menu.Flag = false;
        }
        $(".node-navi").css("max-width", pw + "px");
    },
    Size: function () {
        // 搜索去掉
        $('#fs-frame-search').remove();
        // 收藏工具样式设置
        $("#fs-frame-navi").css({ "float": "left", "left": "320px", "right": "auto" });
        $(".fs-navibar-item").css({ "line-height": "80px", "color": "#ffffff" });
        // 注册信息样式设置两种方式1去掉2修改样式,采用2方式
        var $reg = $('#fs-frame-reg');
        //if ($reg.length > 0) {
        //	$reg.remove();
        //}
        $reg.css({ "float": "left", "left": "80px", "right": "auto", "line-height": "80px" });
        $(".fs-tab-homepage").removeClass("fui-seb");
        $("#fs-frame-body").css("top", "80px");
        $("#fs-frame-body").height($("#fs-frame-body").height() - 20);
        $("#fs-frame-header").css("height", "80px");
        $("#fs-frame-banner").append('<span class="sxs" title="显示"></span>');
        var $a = $(".fs-menutree > ul > li > a.select");
        if ($a.length == 0) {
            $a = $(".fs-menutree > ul > li > a");
        }
        Menu.YC($a);
        $(".sxs").bind("click", function () {
            $(".syc").show();
            var fw = $("#fs-frame-menu").width();
            $("#fs-frame-menu").show();
            $("#fs-frame-content").css("left", fw + "px").width($("#fs-frame-content").width() - fw + 21);
            $(".fs-tab-names").width($(".fs-tab-names").width() - fw + 21);
            $(".fs-tab-content").width($(".fs-tab-content").width() - fw + 21);
            $(".sxs").hide();
        });
        Menu.SetFlag();
    },
    Btn: function () {
        $(".node-navi li").bind("click", function () {
            var xt = $(this).attr("xt");
            if ($(this).hasClass('liss')) {
                if (!Menu.Flag) {
                    $(this).addClass('lius').removeClass('liss');
                    $(".fs-menutree > ul > li ul").hide();
                    Menu.InitAll(xt);
                }
                return;
            }
            // 选中样式设置
            $(".node-navi").find('.liss').removeClass('liss').addClass('lius');
            $(this).addClass('liss');
            Menu.InitTwo(xt);
        });
    },
    YC:function(obj){
        $(obj).eq(0).append('<span class="syc" title="隐藏"></span>');
        $(".syc").bind("click", function () {
            var fw = $("#fs-frame-menu").width();
            $("#fs-frame-menu").hide();
            $("#fs-frame-content").css("left", "21px").width($("#fs-frame-content").width() + fw - 21);
            $(".fs-tab-names").width($(".fs-tab-names").width() + fw - 21);
            $(".fs-tab-content").width($(".fs-tab-content").width() + fw - 21);
            $(".sxs").show();
            $(".syc").hide();
            return false;
        });
    },
    // 一级菜单显示完全，左侧仅显示二级菜单
    InitTwo: function (xt) {
        $(".syc").remove();
        $(".fs-menutree > ul > li").hide();
        $(".fs-menutree > ul > li").eq(xt).show();
        var $a = $(".fs-menutree > ul > li").eq(xt).find("a");
        $a.eq(0).click();
        Menu.YC($a);
        $(".fs-menutree > ul > li").eq(xt).find("ul").eq(0).show();
    },
    // 一级菜单显示不完全，左侧需显示一二两级菜单
    InitAll: function (xt) {
        $(".syc").remove();
        $(".fs-menutree > ul > li").show();
        Menu.YC($(".fs-menutree > ul > li > a"));
    }
};
