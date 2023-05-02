from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
chrome_options = Options()
chrome_options.add_experimental_option("detach", True)
import time

browser = webdriver.Chrome(chrome_options=chrome_options)

# 장인 약과 사이트 열고 로그인하기
browser.get("https://janginthe.com/member/login.html")
id = browser.find_element(By.ID, "member_id")
pw = browser.find_element(By.ID, "member_passwd")
login_btn = browser.find_element(By.CLASS_NAME, "btn_login")
login_btn.click()


input("Start?")

# 관심 상품 등록
browser.get("https://janginthe.com/product/%EC%9D%98%EC%A0%95%EB%B6%80-%EC%9E%A5%EC%9D%B8%ED%95%9C%EA%B3%BC-%EB%AA%BB%EB%82%9C%EC%9D%B4-%EC%95%BD%EA%B3%BC-%ED%8C%8C%EC%A7%80%EC%95%BD%EA%B3%BC/260/category/28/display/1/")
browser.execute_script('add_wishlist(this, true);')
time.sleep(1.0)
alert = browser.switch_to.alert
alert.accept()

# 관심 상품 새로고침 및 모두 구매 무한 반복
while(True):
  try:
    browser.get("https://janginthe.com/myshop/wish_list.html#none")
    result = browser.execute_script("NewWishlist.orderAll();")
    alert = browser.switch_to.alert
    alert.accept()
    time.sleep(0.2)
  except:
    break
# while(True):
#   time.sleep(1.0)

# browser.execute_script('$("span#btnBuy")').click()
# browser.
