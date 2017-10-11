<%@ page contentType="text/html; charset=UTF-8" %><%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%><%@page import="javax.portlet.PortletPreferences" %>
var ImgsMutile = new Object();
ImgsMutile.filesrcs = new Array();
ImgsMutile.filesizes = new Array();

ImgsMutile.insert = function(filesrc,filesize){
	for(var i=0;i<ImgsMutile.filesrcs.length;i++){
		if(filesrc == ImgsMutile.filesrcs[i]){
			return ImgsMutile.filesizes[i];
		}
	}
	
	ImgsMutile.filesrcs.push(filesrc);
	ImgsMutile.filesizes.push(filesize);
};

ImgsMutile.getFilesize = function(imagesrc){
	for(var i=0;i<ImgsMutile.filesrcs.length;i++){
		if(imagesrc == ImgsMutile.filesrcs[i]){
			return ImgsMutile.filesizes[i];
		}
	}
};

ImgsMutile.setOldSrc = function(oldsrc){
	if(oldsrc != null && oldsrc != undefined && oldsrc.length>0){
		this.oldsrc = oldsrc;
	}
};

function preview($div, $src,$obj,$span,$txt1,$txt2,$txt3,$txt4,maxSize,oldImgsMutilerc)
{	
	ImgsMutile.setOldSrc(oldImgsMutilerc)
	var sflag = isImg($src)
    
    var sizeCondition = true;//用来标记上传文件大小是否合格
    
    if(sflag){
    	var image=new Image();
    	var imagescr;
    	var fs;
    	if(navigator.userAgent.indexOf("Firefox")>=0){
    		imagescr = $obj.files.item(0).getAsDataURL();
    		image.onload = imgloaded($obj,$div,$span,sflag,$txt1,$txt2,$txt3,$txt4,image,oldImgsMutilerc,maxSize,imagescr);
    		$div.getElementsByTagName("img")[0].src =  imagescr;
    		
    		image.src=imagescr;
    		image.setAttribute("imagesize",$obj.files.item(0).fileSize);    		
    	}else{
    	   //添加IE8下无法正常获取input[file].value的值
    	   $obj.select();
    	   imagescr = document.selection.createRange().text;
    	   image.onload = imgloaded($obj,$div,$span,sflag,$txt1,$txt2,$txt3,$txt4,image,oldImgsMutilerc,maxSize,imagescr);
	       image.src = imagescr; 
	       
	       $div.style.filter="progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod = scale)";   
		   $div.filters.item("DXImageTransform.Microsoft.AlphaImageLoader").src = imagescr;
		   $div.innerText="";
	   }
	   
	   if(imagescr != null && imagescr != "" && imagescr != undefined){
	   		var filesize = ImgsMutile.getFilesize(imagescr);
	   }
	   if(filesize &&　(filesize>parseInt(maxSize)*1024)){
	   		sizeCondition = false;
			if(navigator.userAgent.indexOf("Firefox")>=0){
	   			if(ImgsMutile.oldsrc != null && ImgsMutile.oldsrc != undefined && ImgsMutile.oldsrc.length>0){
					$div.getElementsByTagName("img")[0].src =  ImgsMutile.oldsrc;
				}else{
					$div.getElementsByTagName("img")[0].src =  oldImgsMutilerc;
				}
	    	}else{
	    	   //添加IE8下无法正常获取input[file].value的值
	           $obj.select();
		       ImgsMutilerc = document.selection.createRange().text; 
		       $div.style.filter="progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod = scale)";   
			  if(ImgsMutile.oldsrc != null && ImgsMutile.oldsrc != undefined && ImgsMutile.oldsrc.length>0){
					$div.filters.item("DXImageTransform.Microsoft.AlphaImageLoader").src =  ImgsMutile.oldsrc;
				}else{
					$div.filters.item("DXImageTransform.Microsoft.AlphaImageLoader").src =  oldImgsMutilerc;
				}
			   $div.innerText="";
		   }
	   }
    }else{
		resetInputMu($txt1,$txt2,$txt3,$txt4,maxSize,$span,sizeCondition);
	}
	
    if($obj.form){
		Validator.ValidateComponent($obj, $obj.name);
	}
}

function imgloaded($obj,$div,$span,sflag,$txt1,$txt2,$txt3,$txt4,image,oldImgsMutilerc,maxSize,filesrc){
	return function(){
		var filesize;
		if(navigator.userAgent.indexOf("Firefox")>=0){
			filesize = image.getAttribute("imagesize");
		}else{
			filesize = image.fileSize;
		}
		
		ImgsMutile.insert(filesrc,filesize);
		
		var sizeCondition = true;
	    if(filesize>parseInt(maxSize)*1024){
			sizeCondition = false;
			if(navigator.userAgent.indexOf("Firefox")>=0){
	   			if(ImgsMutile.oldsrc != null && ImgsMutile.oldsrc != undefined && ImgsMutile.oldsrc.length>0){
					$div.getElementsByTagName("img")[0].src =  ImgsMutile.oldsrc;
				}else{
					$div.getElementsByTagName("img")[0].src =  oldImgsMutilerc;
				}
	    	}else{
	    	   //添加IE8下无法正常获取input[file].value的值
	           $obj.select();
		       ImgsMutilerc = document.selection.createRange().text; 
		       $div.style.filter="progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod = scale)";   
			   if(ImgsMutile.oldsrc != null && ImgsMutile.oldsrc != undefined && ImgsMutile.oldsrc.length>0){
					$div.filters.item("DXImageTransform.Microsoft.AlphaImageLoader").src =  ImgsMutile.oldsrc;
				}else{
					$div.filters.item("DXImageTransform.Microsoft.AlphaImageLoader").src =  oldImgsMutilerc;
				} 
			   $div.innerText="";
		   }
	 	}else{
	 		if(navigator.userAgent.indexOf("Firefox")>=0){
	    		imagescr = $obj.files.item(0).getAsDataURL();
	    		$div.getElementsByTagName("img")[0].src =  imagescr;
	    	}else{
	    	   //添加IE8下无法正常获取input[file].value的值
	    	   $obj.select();
	    	   imagescr = document.selection.createRange().text;
			   $div.filters.item("DXImageTransform.Microsoft.AlphaImageLoader").src = imagescr;
			   $div.innerText="";
		   }
	 	}
	    if(!sflag || !sizeCondition){
	    	resetInputMu($txt1,$txt2,$txt3,$txt4,maxSize,$span,sizeCondition);
	    }
	}
	if($obj.form){
		Validator.ValidateComponent($obj, $obj.name);
	}
}

function resetInputMu($txt1,$txt2,$txt3,$txt4,maxSize,$span,sizeCondition){
	var size = $txt1.value;//file 元素的size 属性
	var name = $txt2.value;//file 元素的name 属性
	var clas = $txt3.value;//file 元素的class 属性
	var prename = $txt4.value;//用于获取该控件的唯一ID
	
	if(!sizeCondition){
		alert("上传图片文件不能大于"+maxSize+" KB");
	}else{
		alert("请上传图片文件");
	}
	var inn = "<input type=\"file\"";
	if(size.length!=0){
		inn = inn +" size=\""+size+"\"";
	}
	
	inn = inn +" name =\""+name+"\"";
	if(clas.length != 0){
		inn = inn +" class=\""+clas+"\"";
	}
	var temp = " preview(preview_"+prename+",this.value,this,previewspan_"+prename+",txt_"+prename+"1,txt_"+prename+"2,txt_"+prename+"3,txt_"+prename+"4,"+maxSize+")";
	inn = inn+" onchange=\""+temp+" \"/>";
	$span.innerHTML = inn;
}

/*
* 用来判断字符串是否还有图片文件后缀
* ImgsMutiletr为一个包含标准图片后缀的字符串
*/
function isImg(ImgsMutiletr){
	var lastpoint = ImgsMutiletr.lastIndexOf(".");
    var sstr = ImgsMutiletr.slice(lastpoint+1,ImgsMutiletr.length);
	if(ImgsMutiletr.length<=0){
	 	return false;
	}
    var sflag = false;
    if(sstr == "bmp" || sstr == "BMP" ){
    	sflag = true;
    }
    if(sstr == "pcx" || sstr == "PCX" ){
    	sflag=true;
    }
    if(sstr == "tiff" || sstr == "TIFF" ){
    	sflag = true;
    }
    if(sstr == "gif" || sstr== "GIF" ){
    	sflag=true;
    }
    if(sstr == "jpeg" || sstr== "JPEG" ){
    	sflag=true;
    }
    if(sstr == "jpg" || sstr== "JPG" ){
    	sflag=true;
    }
    if(sstr == "tga" || sstr== "TGA" ){
    	sflag=true;
    }
    if(sstr == "exif" || sstr== "EXIF" ){
    	sflag=true;
    }
    if(sstr == "fpx" || sstr== "FPX" ){
    	sflag=true;
    }
    if(sstr == "svg" || sstr== "SVG" ){
    	sflag=true;
    }
    if(sstr == "psd" || sstr== "PSD" ){
    	sflag=true;
    }
    if(sstr == "cdr" || sstr== "CDR" ){
    	sflag=true;
    }
    if(sstr == "pcd" || sstr == "PCD" ){
    	sflag=true;
    }
    if(sstr == "png" || sstr == "PNG" ){
    	sflag=true;
    }
    if(sstr == "ufo" || sstr == "UFO" ){
    	sflag=true;
    }
    if(sstr == "eps" || sstr == "EPS" ){
    	sflag=true;
    }
    if(sstr == "hdri" || sstr == "HDRI" ){
    	sflag=true;
    }
    return sflag;
}

function adjustment($img, $div)
{
    var proportion = $div.style.pixelHeight / $div.style.pixelWidth;
    var realProportion = $img.offsetHeight / $img.offsetWidth;
    if ($img.clientWidth > $div.style.pixelWidth || $img.clientHeight > $div.style.pixelHeight) {
        if (realProportion >= 1)
            $img.height = $div.style.pixelHeight - 2;
        else
            $img.width = $div.style.pixelWidth - 2;
    }
    $img.style.top = $div.offsetTop + ($div.style.pixelHeight - $img.clientHeight)/2;
    $img.style.left = $div.offsetLeft + ($div.style.pixelWidth - $img.clientWidth)/2;
}